/* TinyAudioLink - Seamlessly transfer Audio between USB capable devices
 * Copyright (C) 2019 Michael Fabian 'Xaymar' Dirks
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Teensy 4.x Info
 * - FlexSPI NOR Flash uses 256 byte pages with 4096 byte sectors.
 *   - Align to sector, since it speeds up Flash access.
 * - ITCM and DTCM must be initialized by software.
 * - SRAM is run via On-Chip RAM2, near instant access.
 * - FLASH is run via FlexSPI1, max 256MB.
 * - ERAM is run via FlexSPI2, max 240MB.
 */

MEMORY
{
	ITCM (X):  ORIGIN = @BOARD_ITCM@, LENGTH = @BOARD_ITCM_SIZE@
	DTCM (RW):  ORIGIN = @BOARD_DTCM@, LENGTH = @BOARD_DTCM_SIZE@
	SRAM (RWX):  ORIGIN = @BOARD_SRAM@, LENGTH = @BOARD_SRAM_SIZE@
	FLASH (RWX): ORIGIN = @BOARD_FLASH@, LENGTH = @BOARD_FLASH_SIZE@
	ERAM (RWX):  ORIGIN = @BOARD_ERAM@, LENGTH = @BOARD_ERAM_SIZE@
}

ENTRY(_start)

SECTIONS
{
	.flash.headers : ALIGN(4K) {
		. = ORIGIN(FLASH);
		__flash_start = .;

		KEEP(*(.flashLoader))

		/* Image Vector Table
		 * - IMXRT1060RM_rev1_Processor_Manual.pdf: 8.7.1
		 * - IMXRT1060RM_rev3.pdf: 9.7.1
		 *
		 * Location varies by boot type:
		 * - FlexSPI NOR: 0x1000 (4KB, loads everything)
		 * - SD/MMC/...: 0x400 (1KB, loads 4KB only)
		 * - FlexSPI NAND: 0x400 (1KB, loads 4KB only)
		 */
		FILL(0xFFFFFFFF) : . = ORIGIN(FLASH) + 4K;	/* . = ALIGN(4K); */
		KEEP(*(.imageVectorTable))

		/* Boot Data
		 * - Just 12 bytes long, so it fits here.
		 */
		FILL(0xFFFFFFFF) : . = ALIGN(16);
		KEEP(*(.bootData))

		/* Device Configuration Data
		 * - Mostly just used to do pre-boot initialization for jumping into code itself.
		 */
		FILL(0xFFFFFFFF) : . = ALIGN(16);
		KEEP(*(.dcd))

		/* Interrupt Vector Table
		 * - Must be 128 byte aligned.
		 * - We want this to be as early in the Flash as possible.
		 *   - 968 bytes long, so it fits between here and FlexSPI NOR Flash.
		 *   - Does not fit between flashLoader and imageVectorTable for SD/MMC or NAND boot.
		 *   - Just move it to be after imageVectorTable and bootData, filling out the remaining 4K that are loaded anyway.
		 * - Not documented at all? Is relatively easy to figure out anyway.
		 */
		FILL(0xFFFFFFFF) : . = ALIGN(128);
		KEEP(*(.interruptVectorTable))

	} > FLASH =0x00000000

	.flash.code : ALIGN(4K) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		KEEP(*(.text._start))
		*(.flashCode)
	} > FLASH =0x00000000

	.flash.data : ALIGN(4K) {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.flashData)))
	} > FLASH =0x00000000

	.flash.unwind (TYPE=SHT_NOBITS) : ALIGN(4K) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		__exidx_start = .;
		*(.ARM.exidx* .ARM.extab* .gnu.linkonce.armexidx*)
		__exidx_end = .;

	} > FLASH =0x00000000

	.flash.itcm (TYPE=SHT_NOBITS) : {
		PROVIDE_HIDDEN(__itcmStart = .);

		FILL(0x00) : . = . + 32; /* Use Memory Protection Unit to trap a null pointer dereference. */
	} > ITCM AT>FLASH =0x00000000

	.flash.preInit (TYPE=SHT_INIT_ARRAY) : ALIGN(4K) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		PROVIDE_HIDDEN(__preinit_array_start = .);
		KEEP (*(.preinit_array.*))
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN(__preinit_array_end = .);
	} > ITCM AT>FLASH =0x00000000

	.flash.init (TYPE=SHT_INIT_ARRAY) : ALIGN(4K) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		PROVIDE_HIDDEN(__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		PROVIDE_HIDDEN(__init_array_end = .);
		
		KEEP(*(.init))
	} > ITCM AT>FLASH =0x00000000

	.flash.fini (TYPE=SHT_FINI_ARRAY) : ALIGN(4K) {
		PROVIDE_HIDDEN(__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array))
		PROVIDE_HIDDEN(__fini_array_end = .);
		
		KEEP(*(.fini))
	} > ITCM AT>FLASH =0x00000000

	.flash.fastCode : ALIGN(4K) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		*(.fastCode)
		*(.text*)

		PROVIDE_HIDDEN(__itcmEnd = .);
	} > ITCM AT> FLASH =0x00000000
	PROVIDE_HIDDEN(__fast_code_length = __itcmEnd - __itcmStart);
	PROVIDE_HIDDEN(__fast_code_address = LOADADDR(.flash.itcm));

	.flash.fastData : ALIGN(4K) {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata.*)))
		__dtcm_rodata = .;
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.data.*)))
		
		FILL(0xFFFFFFFF);
	} > DTCM AT> FLASH
	PROVIDE_HIDDEN(__fast_data_length = SIZEOF(.flash.fastData));
	PROVIDE_HIDDEN(__fast_data_address = LOADADDR(.flash.fastData));

	.flash.iramCode : ALIGN(4K) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		PROVIDE_HIDDEN(__board_iram = .);
		*(.iramCode);
	} > SRAM AT> FLASH

	.flash.iramData ALIGN(4) : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.iramData)));

		. = ALIGN(4);
		PROVIDE_HIDDEN(__board_iram_free = .);
		PROVIDE_HIDDEN(__heap_start = .);

		FILL(0xFFFFFFFF);
	} > SRAM AT> FLASH
	PROVIDE_HIDDEN(__board_iram_size = @BOARD_SRAM_SIZE@);
	PROVIDE_HIDDEN(__board_iram_address = LOADADDR(.flash.iramCode));
	PROVIDE_HIDDEN(__board_iram_length = __board_iram_free - __board_iram);
	PROVIDE_HIDDEN(__heap_end = __heap_start + __board_iram_length);

	.flash.eramCode : ALIGN(4K) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		PROVIDE_HIDDEN(__board_eram = .);
		*(.eramCode);
	} > ERAM AT> FLASH

	.flash.eramData ALIGN(4) : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.eramData)));

		. = ALIGN(4);
		PROVIDE_HIDDEN(__board_eram_free = .);

		FILL(0xFFFFFFFF);
	} > ERAM AT> FLASH
	PROVIDE_HIDDEN(__board_eram_size = @BOARD_ERAM_SIZE@);
	PROVIDE_HIDDEN(__board_eram_address = LOADADDR(.flash.eramCode));
	PROVIDE_HIDDEN(__board_eram_length = __board_eram_free - __board_eram);

	.flash : {
		PROVIDE_HIDDEN(__flashImageEnd = .);
		PROVIDE_HIDDEN(__flash_length = __flashImageEnd - __flash_start);
	} > FLASH

	.bss ALIGN(4) : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.bss*)))
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(COMMON)))
	} > DTCM
	PROVIDE_HIDDEN(__bss_start = ADDR(.bss));
	PROVIDE_HIDDEN(__bss_length = SIZEOF(.bss));

	/* Calculate the Intruction/Data Tightly Coupled Memory split.
	 * - The granularity of this is only 32KiB (512K / 16).
	 * - While DTCM and ITCM are clear, it isn't clear what OCRAM configuration is for.
	 * - We can also mark things as unused, but really we just want the extra DTCM area for stack.
	 */
	PROVIDE_HIDDEN(__itcm_block_count = (__fast_code_length + 0x7FFF) >> 15);
	PROVIDE_HIDDEN(__flexram_bank_config = 0xAAAAAAAA | ((1 << __itcm_block_count * 2) - 1));

	/* Pass further data for ITCM/DTCM MPU initialization.
	 * - Can use this to trap invalid calls, if there are any.
	 * - Aside from that, not really useful.
	 */
	PROVIDE_HIDDEN(__itcm_start = ORIGIN(ITCM));
	PROVIDE_HIDDEN(__itcm_length = (__itcm_block_count << 15));
	PROVIDE_HIDDEN(__dtcm_start = ORIGIN(DTCM));
	PROVIDE_HIDDEN(__dtcm_length = @BOARD_DTCM_SIZE@ - __itcm_length);
	
	/* Calculate the location of the stack.
	 * - EABI stack grows "up" not down.
	 * - Must offset by 4, as [sp] by default should be a valid address.
	 */
	PROVIDE_HIDDEN(__stack_start = ORIGIN(DTCM) + __dtcm_length);

	/* Handle ARM unwind information.
	 * - It needs to be within -0x40000000 to +0x3FFFFFFF of the C++ code being run.
	 *   - ITCM can reach from [0x00000000] to [0x3FFFFFFF+BOARD_ITCM_SIZE], reaches entirety of DTCM and SRAM.
	 *   - DTCM can reach from [0x00000000] to [0x5FFFFFFF+BOARD_DTCM_SIZE], reaches entirety of ITCM and SRAM.
	 *   - FLASH can reach from [0x20000000+BOARD_FLASH_SIZE] to [0x9FFFFFFF+BOARD_FLASH_SIZE], this reaches DTCM and SRAM, but limits us to 512K of flashCode.
	 * - If we don't fit inside the limit, we get an R_ARM_PREL31 out of range error.
	 * - So for now we discard it, removing exceptions entirely - Teensyduino does this too.
	 */
	/* /DISCARD/ : {
		*(.ARM.exidx* .ARM.extab* .gnu.linkonce.armexidx*)
	} */
	/* .ARM.exidx : { */
	/* 	. = ORIGIN(DTCM); */
	/* 	/* . = ORIGIN(DTCM) + 512K - SIZEOF(.ARM.exidx*) - SIZEOF(.ARM.extab*) - SIZEOF(.gnu.linkonce.armexidx*) - 4K; */
	/* 	*(.ARM.exidx* .ARM.extab* .gnu.linkonce.armexidx*) */
	/* } > DTCM AT> FLASH */
	
#ifdef NDEBUG
	.debug_info     0 : { *(.debug_info) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
#endif
};
