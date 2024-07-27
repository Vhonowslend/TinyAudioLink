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

#include <arm/v7/cache.hpp>
#include <arm/v7/fpu.hpp>
#include <arm/v7/nvic.hpp>
#include <arm/v7/systick.hpp>
#include <arm/v7/v7.hpp>
#include <nxp/imxrt1060/bootdata.hpp>
#include <nxp/imxrt1060/deviceconfigurationdata.hpp>
#include <nxp/imxrt1060/gpio.hpp>
#include <nxp/imxrt1060/imagevectortable.hpp>
#include <nxp/imxrt1060/imxrt1060.hpp>
#include <nxp/kinetis.hpp>

#include <arm/v7/v7.h>
#include <nxp/imxrt1060/imxrt1060.h>
#include "board.h"

extern "C" void _exit(int) noexcept;
extern "C" void _main(void) noexcept;
extern "C" int  main() noexcept;
extern size_t   __flexram_bank_config; // FlexRAM Bank Configuration

extern "C" [[gnu::used, gnu::naked, gnu::section(".flashCode")]]
void __main(void) noexcept
{
	// This is done via DCD as well, but just to be safe on reset, we do it again here.
	// GPR17: Set FLEXRAM_BANK_CFG
	asm volatile("str %[val], %[gpr]"
				 : [gpr] "=g"(__IMXRT1060_IOMUXC_GPR17)
				 : [val] "r"(&__flexram_bank_config)
				 : "memory");

	// This is done via DCD as well, but just to be safe on reset, we do it again here.
	// GPR16: Set v7_INIT_VTOR, and FLEXRAM_BANK_CFG_SEL
	// VTOR: Set Interrupt Vector Table Offset correctly.
	asm volatile(
		"bic %[v7_init_vtor], %[v7_init_vtor_bic];"
		"str %[v7_init_vtor], %[vtor];" // Accepts the same value as GPR16, but ignores the lower 7 bits, so it's
		// better here.
		"orr %[v7_init_vtor], %[v7_init_vtor], %[flexram_bank_cfg_sel];"
		"str %[v7_init_vtor], %[gpr16];"
		: [gpr16] "=g"(__IMXRT1060_IOMUXC_GPR16), [vtor] "=g"(__ARMV7_VTOR)
		: [flexram_bank_cfg_sel] "ir"(0x00000007), [v7_init_vtor_bic] "ir"(0x7F),
		  [v7_init_vtor] "r"(arm::v7::nvic::interrupt_vector_table_ptr)
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
		{ // Initialize Memory
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
				boot_memcpy(BOARD_IRAM_START, BOARD_IRAM_FLASH, BOARD_IRAM_LENGTH);
			}

			if (BOARD_ERAM_LENGTH > 0) { // Initialize ERAM area
				boot_memcpy(BOARD_ERAM_START, BOARD_ERAM_FLASH, BOARD_ERAM_LENGTH);
			}

			{ // Block until sychronized
				arm::v7::instruction_synchronization_barrier();
				arm::v7::data_synchronization_barrier();
				arm::v7::memory_synchronization_barrier();
			}
		}

		{ // Initialize Hardware Features - either this, or deal with forgetting [[gnu::always_inline]]...
			{ // Enable all caches.
				arm::v7::cache::data::enable();
				arm::v7::cache::instruction::enable();
			}

			{ // Enable any available Floating Point Units.
				arm::v7::fpu::enable(); // This is a NOP if it's not supported.
			}

			{ // Enable Sleep and Deep Sleep
				arm::v7::SCR = ((1 << 4 /* Wake Up on Pending Event*/) | (1 << 2 /* Allow using Deep Sleep state */)
								| (1 << 1 /* Return to Sleep when exiting Interrupt Service Routine (ISR) */));
			}

			{ // Block until sychronized
				arm::v7::instruction_synchronization_barrier();
				arm::v7::data_synchronization_barrier();
				arm::v7::memory_synchronization_barrier();
			}
		}

		{ // Do apparently nothing.
			// - Reduce bias current by 30% on ACMP1, ACMP3.
			// - Increase bias current by 30% on ACMP1, ACMP3.
			nxp::imxrt1060::IOMUXC_GPR14 = 0b101010100000000000000000;
		}

		{ // Block until sychronized
			arm::v7::instruction_synchronization_barrier();
			arm::v7::data_synchronization_barrier();
			arm::v7::memory_synchronization_barrier();
		}

		{ // Run main code.
			{ // Run pre-init.
				extern void (*__preinit_array_start[])(void) __attribute__((weak));
				extern void (*__preinit_array_end[])(void) __attribute__((weak));
				for (size_t edx = __preinit_array_end - __preinit_array_start, idx = 0; idx < edx; idx++) {
					__preinit_array_start[idx]();
				}
			}

			{ // Run init.
				extern void (*__init_array_start[])(void) __attribute__((weak));
				extern void (*__init_array_end[])(void) __attribute__((weak));
				for (size_t edx = __init_array_end - __init_array_start, idx = 0; idx < edx; idx++) {
					__init_array_start[idx]();
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
					__fini_array_start[idx]();
				}
			}
		}
	}

	__builtin_unreachable();
}
