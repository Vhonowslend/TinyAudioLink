// TinyAudioLink - Seamlessly transfer Audio between USB capable devices
// Copyright (C) 2019 Michael Fabian 'Xaymar' Dirks
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#import "cinttypes"
#import "cstddef"

#include <arm/cm7/cache.hpp>
#include <arm/cm7/fpu.hpp>
#include <arm/cm7/nvic.hpp>
#include <arm/cm7/systick.hpp>
#include <nxp/imxrt1060/bootdata.hpp>
#include <nxp/imxrt1060/deviceconfigurationdata.hpp>
#include <nxp/imxrt1060/gpio.hpp>
#include <nxp/imxrt1060/imagevectortable.hpp>
#include <nxp/imxrt1060/iomuxc.hpp>
#include <nxp/kinetis.hpp>

#include <arm/cm7/cm7.h>
#include <nxp/imxrt1060/imxrt1060.h>
#include "board.h"

extern "C" void _exit(int) noexcept;
extern "C" void _main(void) noexcept;
extern "C" int  main() noexcept;
extern size_t   __flexram_bank_config; // FlexRAM Bank Configuration
extern void*    __interrupt_vector_table_ptr;

extern "C" [[gnu::used, gnu::naked, gnu::section(".flashCode")]]
void __main(void) noexcept
{
	// Seems like we're offset by one byte exactly?
	asm volatile("nop");

	// GPR17: Set FLEXRAM_BANK_CFG
	asm volatile("str %[val], %[gpr]"
				 : [gpr] "=g"(__IMXRT1060_IOMUXC_GPR17)
				 : [val] "r"(&__flexram_bank_config)
				 : "memory");

	// GPR16: Set CM7_INIT_VTOR, and FLEXRAM_BANK_CFG_SEL
	// VTOR: Set Interrupt Vector Table Offset correctly.
	asm volatile(
		"bic %[cm7_init_vtor], %[cm7_init_vtor_bic];"
		"str %[cm7_init_vtor], %[vtor];" // Accepts the same value as GPR16, but ignores the lower 7 bits, so it's
										 // better here.
		"orr %[cm7_init_vtor], %[cm7_init_vtor], %[flexram_bank_cfg_sel];"
		"str %[cm7_init_vtor], %[gpr16];"
		: [gpr16] "=g"(__IMXRT1060_IOMUXC_GPR16), [vtor] "=g"(__CORTEXM7_VTOR)
		: [flexram_bank_cfg_sel] "ir"(0x00000007), [cm7_init_vtor_bic] "ir"(0x7F),
		  [cm7_init_vtor] "r"(__interrupt_vector_table_ptr)
		: "r0", "memory");

	// Reset the stack pointer if we somehow ended up back here unexpectedly.
	asm volatile("mov sp, %[stack]" : : [stack] "r"(&__stack_start) : "sp", "memory");

	// Wait until everything has synchronized as expected again.
	asm volatile("isb;dsb;dmb" ::: "memory");

	// Then jump to the initialization routine of the board.
	asm volatile("b %P0" : : "i"(&_main));
}

extern "C" [[gnu::section(".flashCode")]]
void boot_memcpy(void* dest, const void* src, size_t count) noexcept
{
	uint8_t*       dest8 = reinterpret_cast<uint8_t*>(dest);
	const uint8_t* src8  = reinterpret_cast<const uint8_t*>(src);
	for (size_t i = 0; i < count; i++) {
		*(dest8++) = *(src8++);
	}
}

extern "C" [[gnu::section(".flashCode")]]
void boot_memset(void* dest, uint8_t value, size_t count) noexcept
{
	uint8_t* dest8 = reinterpret_cast<uint8_t*>(dest);
	for (size_t i = 0; i < count; i++) {
		*(dest8++) = value;
	}
}

extern "C" [[gnu::used, gnu::section(".flashCode")]]
void _main(void) noexcept
{
	while (true) {
		{ // Enable all caches.
			arm::cm7::cache::data::enable();
			arm::cm7::cache::instruction::enable();
		}

		{ // Enable any available Floating Point Units.
			arm::cm7::fpu::enable(); // This is a NOP if it's not supported.
		}

		// Wait until everything is synchronized again.
		asm volatile("isb;dsb;dmb" ::: "memory");

		{ // Initialize ITCM area
			boot_memcpy(BOARD_ITCM_START, BOARD_ITCM_FLASH, BOARD_ITCM_LENGTH);
		}

		{ // Initialize DTCM area
			// The stack is prior to the data, so we don't want to mess with it.
			boot_memcpy(BOARD_DTCM_DATA_START, BOARD_DTCM_DATA_FLASH, BOARD_DTCM_DATA_LENGTH);
			if (false) { // Optionally, zero out BSS, TBSS, SBSS, EH_Frame, etc...
				extern std::size_t __bss_start; // BSS Start
				extern std::size_t __bss_end; // BSS End
				boot_memset(&__bss_start, 0x00,
							reinterpret_cast<std::size_t>(((size_t)&__bss_end - (size_t)&__bss_start)));
				extern std::size_t __tbss_start; // BSS Start
				extern std::size_t __tbss_end; // BSS End
				boot_memset(&__tbss_start, 0x00,
							reinterpret_cast<std::size_t>((size_t)&__tbss_end - (size_t)&__tbss_start));
				extern std::size_t __eh_frame_start; // BSS Start
				extern std::size_t __eh_frame_length; // BSS End
				boot_memset(&__eh_frame_start, 0x00, reinterpret_cast<std::size_t>(&__eh_frame_length));
			}
		}

		if (BOARD_IRAM_LENGTH > 0) { // Initialize IRAM area
			//	boot_memcpy(BOARD_IRAM_START, BOARD_IRAM_FLASH, BOARD_IRAM_LENGTH);
		}

		if (BOARD_ERAM_LENGTH > 0) { // Initialize ERAM area
			//	boot_memcpy(BOARD_ERAM_START, BOARD_ERAM_FLASH, BOARD_ERAM_LENGTH);
		}

		// Wait until everything is synchronized again.
		asm volatile("dmb;dsb;isb;" ::: "memory");

		{ // Do apparently nothing.
			// - Reduce bias current by 30% on ACMP1, ACMP3.
			// - Increase bias current by 30% on ACMP1, ACMP3.
			nxp::imxrt1060::iomuxc::gpr::GPR14 = 0b101010100000000000000000;
		}

		{ // Enable SysTick timer support.
			arm::cm7::systick::initialize();
		}

		// Wait until everything is synchronized again.
		asm volatile("dmb;dsb;isb;" ::: "memory");

		{ // Run pre-init.
			extern void (*__preinit_array_start[])(void) __attribute__((weak));
			extern void (*__preinit_array_end[])(void) __attribute__((weak));
			for (size_t edx = __preinit_array_end - __preinit_array_start, idx = 0; idx < edx; idx++) {
				//				__preinit_array_start[idx]();
			}
		}

		{ // Run init.
			extern void (*__init_array_start[])(void) __attribute__((weak));
			extern void (*__init_array_end[])(void) __attribute__((weak));
			for (size_t edx = __init_array_end - __init_array_start, idx = 0; idx < edx; idx++) {
				//				__init_array_start[idx]();
			}
		}

// Run main.
#ifdef __cpp_exceptions
		try {
#endif
			main();
#ifdef __cpp_exceptions
		} catch (...) {
		}
#endif

		{ // Run fini.
			extern void (*__fini_array_start[])(void) __attribute__((weak));
			extern void (*__fini_array_end[])(void) __attribute__((weak));
			for (size_t edx = __fini_array_end - __fini_array_start, idx = 0; idx < edx; idx++) {
				//				__fini_array_start[idx]();
			}
		}
	}

	__builtin_unreachable();
}
