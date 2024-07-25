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
 * - IRAM is run via On-Chip RAM2, near instant access.
 * - FLASH is run via FlexSPI1, max 256MB.
 * - ERAM is run via FlexSPI2, max 240MB.
 */

MEMORY
{
	ITCM (X):  ORIGIN = @BOARD_ITCM@, LENGTH = @BOARD_ITCM_SIZE@
	DTCM (RW):  ORIGIN = @BOARD_DTCM@, LENGTH = @BOARD_DTCM_SIZE@
	IRAM (RWX):  ORIGIN = @BOARD_IRAM@, LENGTH = @BOARD_IRAM_SIZE@
	FLASH (RWX): ORIGIN = @BOARD_FLASH@, LENGTH = @BOARD_FLASH_SIZE_LINK@
	ERAM (RWX):  ORIGIN = @BOARD_ERAM@, LENGTH = @BOARD_ERAM_SIZE@
}

ENTRY(__main)

SECTIONS
{
	.flash.headers (TYPE = SHT_PROGBITS) : ALIGN(32) {
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
		FILL(0x00000000) : . = ORIGIN(FLASH) + 4K;	/* . = ALIGN(256); */
		KEEP(*(.imageVectorTable))

		/* Boot Data
		 * - Just 12 bytes long, so it fits here.
		 */
		FILL(0x00000000) : . = ALIGN(16);
		KEEP(*(.bootData))

		/* Device Configuration Data
		 * - Mostly just used to do pre-boot initialization for jumping into code itself.
		 */
		FILL(0x00000000) : . = ALIGN(16);
		KEEP(*(SORT_BY_NAME(.dcd)))

		/* Interrupt Vector Table
		 * - Must be aligned to 128 bytes, due to CM7_INIT_VTOR limitations.
		 * - We want this to be as early in the Flash as possible.
		 *   - 968 bytes long, so it fits between here and FlexSPI NOR Flash.
		 *   - Does not fit between flashLoader and imageVectorTable for SD/MMC or NAND boot.
		 *   - Just move it to be after imageVectorTable and bootData, filling out the remaining 4K that are loaded anyway.
		 * - Not documented at all? Is relatively easy to figure out anyway.
		 */
		FILL(0x00000000) : . = ALIGN(128);
		KEEP(*(.interruptVectorTable))
	} >FLASH =0xFFFFFFFF

	.flash.code : ALIGN(4K) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		*(.flashCode)
	} >FLASH =0xFFFFFFFF

	.flash.preInit (TYPE=SHT_INIT_ARRAY) : ALIGN(32) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		PROVIDE_HIDDEN(__preinit_array_start = .);
		*(.preinit_array.*)
		*(.preinit_array)
		PROVIDE_HIDDEN(__preinit_array_end = .);
	} >FLASH =0xFFFFFFFF

	.flash.init (TYPE=SHT_INIT_ARRAY) : ALIGN(32) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		PROVIDE_HIDDEN(__init_array_start = .);
		*(.init_array.*)
		*(.init_array)
		PROVIDE_HIDDEN(__init_array_end = .);

		KEEP(*(.init))
	} >FLASH =0xFFFFFFFF

	.flash.fini (TYPE=SHT_FINI_ARRAY) : ALIGN(32) {
		PROVIDE_HIDDEN(__fini_array_start = .);
		*(.fini_array.*)
		*(.fini_array)
		PROVIDE_HIDDEN(__fini_array_end = .);

		KEEP(*(.fini))
	} >FLASH =0xFFFFFFFF

	.flash.eh_frame_hdr : ALIGN(32) {
		PROVIDE_HIDDEN(__eh_frame_hdr_start = .);
		*(.eh_frame_hdr)
		PROVIDE_HIDDEN(__eh_frame_hdr_end = .);
	} >FLASH =0xFFFFFFFF

	.flash.eh_frame : ALIGN(32) {
		PROVIDE_HIDDEN(__eh_frame_start = .);
		*(.eh_frame)
		PROVIDE_HIDDEN(__eh_frame_end = .);
	} >FLASH =0xFFFFFFFF

	.flash.exidx (TYPE=SHT_NOBITS) : ALIGN(32) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		PROVIDE_HIDDEN(__exidx_start = .);
		*(.ARM.exidx* .ARM.extab* .gnu.linkonce.armexidx*)
		PROVIDE_HIDDEN(__exidx_end = .);
	} >FLASH =0xFFFFFFFF

	.flash.data : ALIGN(4K) {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.flashData)))
	} >FLASH =0xFFFFFFFF

	/** Tightly Coupled Memory
	 * We can significantly speed up memory access using FlexRAM configuration,
	 * however we can only do this with the first 512K of memory. 
	 *
	 * We use this area for fast code, fast data, and the stack. The stack will
	 * be at the end of the DTCM area, growing up. It therefore has the possibility
	 * of smashing into data and code, which is unfortunate - but mostly 
	 * unavoidable.
	 */
	.itcm : ALIGN(32) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		PROVIDE_HIDDEN(__itcm_start = .);
		. = . + 32; /* Use Memory Protection Unit to trap a null pointer dereference. */

		*(.text*)
		*(.fastCode)

		PROVIDE_HIDDEN(__itcm_end = .);
	} >ITCM AT>FLASH =0xFFFFFFFF
	PROVIDE_HIDDEN(__itcm_addr = LOADADDR(.itcm));
	PROVIDE_HIDDEN(__itcm_length = (__itcm_end - __itcm_start));
	PROVIDE_HIDDEN(__itcm_block_count = (__itcm_length + 0x7FFF) >> 15);

	.dtcm : ALIGN(32) {
		PROVIDE_HIDDEN(__dtcm_start = .);
	} >DTCM AT>FLASH =0xFFFFFFFF

	.dtcm.stack (NOLOAD) : ALIGN(32) {
		/* Stack Location
		 * - PUSH is an alias for STMDB, POP is an alias for LDMIA
		 * - PUSH automatically decrements SP by 4 for every register, so no manual adjustment needed.
		 * - Stack grows "down" by default, so we should place it at the start for safety.
		 * - Limited in size by compile-time options, but still better than stack smashing our stuff.
		 */
		PROVIDE_HIDDEN(__stack_end = .);
		. = . + @TEENSY_STACK_SIZE@;
		PROVIDE_HIDDEN(__stack_start = .);
	} >DTCM =0xFFFFFFFF

	.dtcm.data : ALIGN(32) {
		/** Initialized Data (Global or Thread-Local)
		 */
		PROVIDE_HIDDEN(__dtcm_data_start = .);
		// Global Data
		*(.data .data.* .gnu.linkonce.d.*)
		// Thread-Local Data
		*(.tdata .tdata.* .tdata1 .tdata1.* .gnu.linkonce.td.*)

		// Shorter Address Data (not used?)
		*(.sdata .sdata.* .sdata2.* .gnu.linkonce.s.*)

		/** Fast Data (manually marked)
		 */
		*(.fastData)
		PROVIDE_HIDDEN(__dtcm_data_end = .);
	} >DTCM AT>FLASH =0xFFFFFFFF
	PROVIDE_HIDDEN(__dtcm_data_addr = LOADADDR(.dtcm.data));
	PROVIDE_HIDDEN(__dtcm_data_length = (__dtcm_data_end - __dtcm_data_start));
	
	/** Uninitialized Data (Shorter Addressing)
	 */
	.dtcm.sbss (NOLOAD) : ALIGN(32) {
		PROVIDE_HIDDEN(__bss_start = .);
		*(.sbss*)
		*(.gnu.linkonce.sb.*)
		PROVIDE_HIDDEN(__bss_end = .);
	} >DTCM AT>FLASH =0xFFFFFFFF

	/** Uninitialized Data (Global)
	 */
	.dtcm.bss (NOLOAD) : ALIGN(32) {
		PROVIDE_HIDDEN(__bss_start = .);
		// Shorter Address Data (not used?)
		//*(.sbss*)
		//*(.gnu.linkonce.sb.*)

		// Global Data
		*(.bss .bss.*)
		*(.gnu.linkonce.b.*)
		*(COMMON)
		PROVIDE_HIDDEN(__bss_end = .);
	} >DTCM AT>FLASH =0xFFFFFFFF

	/** Uninitialized Data (Thread-Local)
	 */
	.dtcm.tbss (NOLOAD) : ALIGN(32) {
		PROVIDE_HIDDEN(__tbss_start = .);
		// Thread-Local Data
		*(.tbss .tbss.*)
		*(.gnu.linkonce.tb.*)
		*(.tcommon)
		PROVIDE_HIDDEN(__tbss_end = .);
	} >DTCM AT>FLASH =0xFFFFFFFF

	.dtcm : {
		PROVIDE_HIDDEN(__dtcm_end = .);
	} >DTCM =0xFFFFFFFF

	/* Calculate the Intruction/Data Tightly Coupled Memory split.
	 * - The granularity of this is only 32KiB (512K / 16).
	 * - While DTCM and ITCM are clear, it isn't clear what OCRAM configuration is for.
	 * - We can also mark things as unused, but really we just want the extra DTCM area for stack.
	 */
	PROVIDE_HIDDEN(__flexram_bank_config = 0xAAAAAAAA | ((1 << __itcm_block_count * 2) - 1));

	/** 2nd half of memory, usually used for DMA only. 
	 * Significantly slower than the first half, and unfortunately not continuous
	 * with DTCM, so we can't seamlessly traverse the memory boundary. We'll be
	 * using this for less important information that doesn't need to be written to
	 * often, but still may be read often - the built-in cache in the chip should
	 * be able to offset this. 
	 */
	.iram (TYPE = SHT_PROGBITS) : ALIGN(32) {
		PROVIDE_HIDDEN(__iram_start = .);
	} >IRAM AT>FLASH =0xFFFFFFFF
	PROVIDE_HIDDEN(__iram_addr = LOADADDR(.iram));

	.iram.code : ALIGN(32) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		*(__lcxx_override);
		*(.iramCode);
		PROVIDE_HIDDEN(__iram_code_end = .);
	} >IRAM AT>FLASH =0xFFFFFFFF

	.iram.data : ALIGN(32) {
		*(.rodata*)
		*(.iramData);

		. = ALIGN(256);
		//PROVIDE_HIDDEN(__iram_end = .);
	} >IRAM AT>FLASH =0xFFFFFFFF

	.iram : {
		PROVIDE_HIDDEN(__iram_end = .);
	} >IRAM =0xFFFFFFFF
	PROVIDE_HIDDEN(__iram_length = __iram_end - __iram_start);

	/** Heap Location
	 * We place the heap into the 2nd half of the on-board memory, which isn't
	 * accessed via DTCM. 
	 */
	.iram.heap (NOLOAD) : ALIGN(32) {
		PROVIDE_HIDDEN(__heap_start = .);
	} >IRAM =0xFFFFFFFF
	PROVIDE_HIDDEN(__heap_end = (@BOARD_IRAM@ + @BOARD_IRAM_SIZE@) - __iram_length);

	.eram : ALIGN(32) {
		PROVIDE_HIDDEN(__eram_start = .);
	} >ERAM AT>FLASH =0xFFFFFFFF
	PROVIDE_HIDDEN(__eram_addr = LOADADDR(.eram));

	.eram.code : ALIGN(32) {
		FLAGS(SHF_EXECINSTR | SHF_LINK_ORDER);

		*(.eramCode);
	} >ERAM AT>FLASH =0xFFFFFFFF

	.eram.data : ALIGN(32) {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.eramData)));

		. = ALIGN(8);
	} >ERAM AT>FLASH =0xFFFFFFFF

	.eram : {
		PROVIDE_HIDDEN(__eram_end = .);
	} >ERAM =0xFFFFFFFF
	PROVIDE_HIDDEN(__eram_length = __eram_end - __eram_start);

	.flash (TYPE = SHT_NOBITS) : {
		PROVIDE_HIDDEN(__flash_end = .);
		PROVIDE_HIDDEN(__flash_length = __flash_end - __flash_start);
	} >FLASH =0xFFFFFFFF
};
