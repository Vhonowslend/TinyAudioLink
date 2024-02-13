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

MEMORY
{
	ITCM (rwx):  ORIGIN = 0x00000000, LENGTH = 512K
	DTCM (rwx):  ORIGIN = 0x20000000, LENGTH = 512K
	RAM (rwx):   ORIGIN = 0x20200000, LENGTH = 512K
	FLASH (rwx): ORIGIN = 0x60000000, LENGTH = 7936K
	ERAM (rwx):  ORIGIN = 0x70000000, LENGTH = 16384K
}

ENTRY(__imageVectorTable)

SECTIONS
{
	.text.headers : {
		KEEP(*(.flashLoader))
		FILL(0xFF)

		/* Image Vector Table
		 * - IMXRT1060RM_rev1_Processor_Manual.pdf: 8.7.1
		 * 
		 * Location varies by boot type:
		 * - FlexSPI NOR: 0x1000 (4KB, loads everything)
		 * - SD/MMC/...: 0x400 (1KB, loads 4KB only)
		 * - FlexSPI NAND: 0x400 (1KB, loads 4KB only)
		 */
		. = ORIGIN(FLASH) + 0x1000;
		KEEP(*(.imageVectorTable))
		KEEP(*(.bootData))
		. = ALIGN(1024);
	} > FLASH

	.text.code : {
		KEEP(*(.startup))
		*(.flashmem*)
		. = ALIGN(4);
		KEEP(*(.init))
		__preinit_array_start = .;
		KEEP (*(.preinit_array))
		__preinit_array_end = .;
		__init_array_start = .;
		KEEP (*(.init_array))
		__init_array_end = .;
		. = ALIGN(4);
	} > FLASH

	.text.progmem : {
		*(.progmem*)
		. = ALIGN(4);
	} > FLASH

	.text.itcm : {
		. = . + 32; /* MPU to trap NULL pointer deref */
		*(.fastrun)
		*(.text*)
		. = ALIGN(16);
	} > ITCM  AT> FLASH

	/* Included by Teensyduino, but unclear why. Does not seem to have a use.
	 * 	.ARM.exidx : {
	 * 	__exidx_start = .;
	 * 	*(.ARM.exidx* .ARM.extab.text* .gnu.linkonce.armexidx.*)
	 * 	__exidx_end = .;
	 * } > ITCM  AT> FLASH
	 */
	/DISCARD/ : {
		*(.ARM.exidx* .ARM.extab.text* .gnu.linkonce.armexidx.*)
	} 
	
	.data : {
    	*(.endpoint_queue)    
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.data*)))
   		 KEEP(*(.vectorsram))
	} > DTCM  AT> FLASH

	.bss ALIGN(4) : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.bss*)))
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(COMMON)))
		. = ALIGN(32);
		. = . + 32; /* MPU to trap stack overflow */
	} > DTCM

	.bss.dma (NOLOAD) : {
		*(.hab_log)
		*(.dmabuffers)
		. = ALIGN(32);
	} > RAM

	/* CSF for HAB, which is not used. Still going to keep it i guess. */
	.text.csf : {
		FILL(0xFF)
		. = ALIGN(1024);
		KEEP(*(.csf))
		__text_csf_end = .;
	} > FLASH

	.text.fin : {
		/* Ensure the end address is aligned to a page, improves speed. */
		. = ALIGN(1024);
		__flashImageEnd = .;
	} > FLASH

	__flashImageLength = __flashImageEnd - ORIGIN(FLASH);

/*	_ITCM_BLOCK_COUNT = (SIZEOF(.text.itcm) + 0x7FFE) >> 15;
	_FLEXRAM_BANK_CONFIG = 0xAAAAAAAA | ((1 << (_ITCM_BLOCK_COUNT * 2)) - 1);
	_STACK_END = ORIGIN(DTCM) + ((16 - _ITCM_BLOCK_COUNT) << 15);

	_TEXT_START = ADDR(.text.itcm);
	_TEXT_END = ADDR(.text.itcm) + SIZEOF(.text.itcm);
	_TEXT_LEN = SIZEOF(.text.itcm);
	_TEXT_LOAD = LOADADDR(.text.itcm);
	
	_DATA_START = ADDR(.data);
	_DATA_END = ADDR(.data) + SIZEOF(.data);
	_DATA_LEN = SIZEOF(.data);
	_DATA_LOAD = LOADADDR(.data);

	_BSS_START = ADDR(.bss);
	_BSS_END = ADDR(.bss) + SIZEOF(.bss);
	_BSS_LEN = SIZEOF(.bss); */

	/* Defined here to avoid rough casting in Rust */
/*	_INITIAL_STACK = 0x20010000; */

	/* From Teensyduino */
/*	_heap_start = ADDR(.bss.dma) + SIZEOF(.bss.dma);
	_heap_end = ORIGIN(RAM) + LENGTH(RAM);

	_flashimagelen = SIZEOF(.text.progmem) + SIZEOF(.text.itcm) + SIZEOF(.data);
	_teensy_model_identifier = 0x24;

	.debug_info     0 : { *(.debug_info) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) } */
};
