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
	.flash.headers ALIGN(4K) : {
		. = ORIGIN(FLASH);
		__flashImageStart = .;

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
		. = ORIGIN(FLASH) + 4K;	/* . = ALIGN(4K); */
		KEEP(*(.imageVectorTable))

		/* Boot Data
		 * - Just 12 bytes long, so it fits here.
		 */
		. = ALIGN(4);
		KEEP(*(.bootData))

		/* Interrupt Vector Table
		 * - Must be 128 byte aligned.
		 * - We want this to be as early in the Flash as possible.
		 *   - 968 bytes long, so it fits between here and FlexSPI NOR Flash.
		 *   - Does not fit between flashLoader and imageVectorTable for SD/MMC or NAND boot.
		 *   - Just move it to be after imageVectorTable and bootData, filling out the remaining 4K that are loaded anyway.
		 * - Not documented at all? Is relatively easy to figure out anyway.
		 */
		. = ALIGN(128);
		KEEP(*(.interruptVectorTable))
	} > FLASH

	.flash.code ALIGN(4K) : {
		KEEP(*(.text._start))		
		*(.flashCode)
	} > FLASH

	.flash.data ALIGN(4K) : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.flashData)))
	} > FLASH

	.flash.fastCode ALIGN(8) : {
		. = . + 32; /* Use Memory Protection Unit to trap a null pointer dereference. */

		KEEP(*(.init))
		KEEP(*(.fini))

		PROVIDE_HIDDEN(__preinit_array_start = .);
		KEEP (*(SORT(.preinit_array.*)))
		KEEP (*(.preinit_array))
		PROVIDE_HIDDEN(__preinit_array_end = .);

		PROVIDE_HIDDEN(__init_array_start = .);
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		PROVIDE_HIDDEN(__init_array_end = .);

		PROVIDE_HIDDEN(__fini_array_start = .);
		KEEP (*(SORT(.fini_array.*)))
		KEEP (*(.fini_array))
		PROVIDE_HIDDEN(__fini_array_end = .);

		*(.fastCode)
		*(.text*)
	} > ITCM AT> FLASH
	__fastCodeLength = SIZEOF(.flash.fastCode);
	__fastCodeAddress = LOADADDR(.flash.fastCode);

	.flash.fastData ALIGN(4) : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata.*)))
		__dtcmReadOnlyData = .;
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.data.*)))
	} > DTCM AT> FLASH
	__fastDataLength = SIZEOF(.flash.fastData);
	__fastDataAddress = LOADADDR(.flash.fastData);

	.flash.iramCode ALIGN(8) : {
		__board_iram = .;
		*(.iramCode);
	} > SRAM AT> FLASH

	.flash.iramData ALIGN(4) : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.iramData)));

		. = ALIGN(4);
		__board_iram_free = .;
	} > SRAM AT> FLASH
	__board_iram_size = @BOARD_SRAM_SIZE@;
	__board_iram_address = LOADADDR(.flash.iramCode);
	__board_iram_length = __board_iram_free - __board_iram;

	.flash.eramCode ALIGN(8) : {
		__board_eram = .;
		*(.eramCode);
	} > SRAM AT> FLASH

	.flash.eramData ALIGN(4) : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.eramData)));

		. = ALIGN(4);
		__board_eram_free = .;
	} > SRAM AT> FLASH
	__board_eram_size = @BOARD_SRAM_SIZE@;
	__board_eram_address = LOADADDR(.flash.eramCode);
	__board_eram_length = __board_eram_free - __board_eram;

	.flash : {
		__flashImageEnd = .;
		__flashImageLength = __flashImageEnd - __flashImageStart;
	} > FLASH

	.bss ALIGN(4) : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.bss*)))
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(COMMON)))
	} > DTCM
	__bssStart = ADDR(.bss);
	__bssLength = SIZEOF(.bss);

	/* Calculate the Intruction/Data Tightly Coupled Memory split.
	 * - The granularity of this is only 32KiB (512K / 16).
	 * - While DTCM and ITCM are clear, it isn't clear what OCRAM configuration is for.
	 * - We can also mark things as unused, but really we just want the extra DTCM area for stack.
	 */
	__itcmBlockCount = (__fastCodeLength + 0x7FFF) >> 15;
	__flexramBankConfig = 0xAAAAAAAA | ((1 << __itcmBlockCount * 2) - 1);

	/* Pass further data for ITCM/DTCM MPU initialization.
	 * - Can use this to trap invalid calls, if there are any.
	 * - Aside from that, not really useful.
	 */
	__itcmStart = ORIGIN(ITCM);
	__itcmLength = (__itcmBlockCount << 15);
	__dtcmStart = ORIGIN(DTCM);
	__dtcmLength = @BOARD_DTCM_SIZE@ - __itcmLength;
	
	/* Calculate the location of the stack.
	 * - EABI stack grows "up" not down.
	 * - Must offset by 4, as [sp] by default should be a valid address.
	 */
	__stackStart = ORIGIN(DTCM) + __dtcmLength - 4;

	/* Handle ARM unwind information.
	 * - It needs to be within -0x40000000 to +0x3FFFFFFF of the C++ code being run.
	 *   - ITCM can reach from [0x00000000] to [0x3FFFFFFF+BOARD_ITCM_SIZE], reaches entirety of DTCM and SRAM.
	 *   - DTCM can reach from [0x00000000] to [0x5FFFFFFF+BOARD_DTCM_SIZE], reaches entirety of ITCM and SRAM.
	 *   - FLASH can reach from [0x20000000+BOARD_FLASH_SIZE] to [0x9FFFFFFF+BOARD_FLASH_SIZE], this reaches DTCM and SRAM, but limits us to 512K of flashCode.
	 * - If we don't fit inside the limit, we get an R_ARM_PREL31 out of range error.
	 * - So for now we discard it, removing exceptions entirely - Teensyduino does this too.
	 */
	/DISCARD/ : {
		*(.ARM.exidx* .ARM.extab* .gnu.linkonce.armexidx*)
	}
	/* .ARM.exidx : { */
	/* 	. = ORIGIN(DTCM); */
	/* 	/* . = ORIGIN(DTCM) + @BOARD_DTCM_SIZE@ - SIZEOF(.ARM.exidx*) - SIZEOF(.ARM.extab*) - SIZEOF(.gnu.linkonce.armexidx*) - 4K; */
	/* 	*(.ARM.exidx* .ARM.extab* .gnu.linkonce.armexidx*) */
	/* } > DTCM AT> FLASH */
	
	.debug_info     0 : { *(.debug_info) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
};
