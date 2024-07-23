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

#include "boot.h"
#include <arm/cm7/cache.hpp>
#include <arm/cm7/cm7.hpp>
#include <arm/cm7/fpu.hpp>
#include <cinttypes>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <nxp/imxrt1060/bootdata.hpp>
#include <nxp/imxrt1060/gpio.hpp>
#include <nxp/imxrt1060/imagevectortable.hpp>
#include <nxp/imxrt1060/iomuxc.hpp>
#include <nxp/imxrt1060/nvic.hpp>
#include <nxp/kinetisflashloader.hpp>
#include "board.h"

// Main Application
extern "C" int main();

extern "C" [[gnu::section(".flashCode")]]
void boot_memcpy(void* dest, const void* src, size_t count)
{
	uint8_t*       dest8 = reinterpret_cast<uint8_t*>(dest);
	const uint8_t* src8  = reinterpret_cast<const uint8_t*>(src);
	for (size_t i = 0; i < count; i++) {
		*(dest8++) = *(src8++);
	}
}

extern "C" [[gnu::section(".flashCode")]]
void boot_memset(void* dest, uint8_t value, size_t count)
{
	uint8_t* dest8 = reinterpret_cast<uint8_t*>(dest);
	for (size_t i = 0; i < count; i++) {
		*(dest8++) = value;
	}
}

extern "C" [[gnu::used, gnu::noreturn, gnu::section(".flashCode")]]
void _start(void)
{
	try {
		{ // Enable all caches.
			asm volatile("dmb;dsb;isb;" ::: "memory");
			arm::cm7::cache::data::enable();
			arm::cm7::cache::instruction::enable();
		}

		{ // Enable any available Floating Point Units.
			arm::cm7::fpu::enable(); // This is a NOP if it's not supported.
		}

		{ // Initialize ITCM
			extern std::size_t __fast_code_length; // Flash Fast Code End
			extern std::size_t __fast_code_address; // Flash Fast Code Address
			extern std::size_t __itcm_start; // ITCM Address
			boot_memcpy(&__itcm_start, &__fast_code_address, reinterpret_cast<std::size_t>(&__fast_code_length));
		}

		{ // Initialize DTCM
			extern std::size_t __fast_data_length; // Flash Fast Data End
			extern std::size_t __fast_data_address; // Flash Fast Data Address
			extern std::size_t __dtcm_start; // DTCM Address
			boot_memcpy(&__dtcm_start, &__fast_data_address, reinterpret_cast<std::size_t>(&__fast_data_length));
		}

		// Wait until everything is synchronized again.
		asm volatile("dmb;dsb;isb;" ::: "memory");

		if (false) { // Zero BSS area
			extern std::size_t __bss_start; // BSS Start
			extern std::size_t __bss_length; // BSS End
			boot_memset(&__bss_start, 0x00, reinterpret_cast<std::size_t>(&__bss_length));
		}

		// Initialize Internal Memory
		if (BOARD_IRAM_SIZE > 0) {
			extern std::size_t __board_iram_address;
			extern std::size_t __board_iram_length;
			boot_memcpy(BOARD_IRAM, &__board_iram_address, reinterpret_cast<std::size_t>(&__board_iram_length));
		}

		// Initialize External Memory
		if (BOARD_ERAM_SIZE > 0) {
			extern std::size_t __board_eram_address;
			extern std::size_t __board_eram_length;
			boot_memcpy(BOARD_ERAM, &__board_eram_address, reinterpret_cast<std::size_t>(&__board_eram_length));
		}

		// Wait until everything is synchronized again.
		asm volatile("dmb;dsb;isb;" ::: "memory");

		// Do apparently nothing.
		// - Reduce bias current by 30% on ACMP1, ACMP3.
		// - Increase bias current by 30% on ACMP1, ACMP3.
		nxp::imxrt1060::iomuxc::gpr::GPR14 = 0b101010100000000000000000;

		// Set up NVIC properly.
		nxp::imxrt1060::nvic::initialize();

		// Run pre-init.
		{
			extern void (*__preinit_array_start[])(void) __attribute__((weak));
			extern void (*__preinit_array_end[])(void) __attribute__((weak));
			for (size_t edx = __preinit_array_end - __preinit_array_start, idx = 0; idx < edx; idx++) {
				__preinit_array_start[idx]();
			}
		}

		// Run init.
		{
			extern void (*__init_array_start[])(void) __attribute__((weak));
			extern void (*__init_array_end[])(void) __attribute__((weak));
			for (size_t edx = __init_array_end - __init_array_start, idx = 0; idx < edx; idx++) {
				__init_array_start[idx]();
			}
		}

		// Run main.
		main();

		// Run fini.
		{
			extern void (*__fini_array_start[])(void) __attribute__((weak));
			extern void (*__fini_array_end[])(void) __attribute__((weak));
			for (size_t edx = __fini_array_end - __fini_array_start, idx = 0; idx < edx; idx++) {
				__fini_array_start[idx]();
			}
		}
	} catch (...) {
		exit(1);
	}

	__builtin_unreachable();

	// If this returns, the chip "crashes" and we usually reset anyway in that case.
	// ToDo: Forcefully trigger a reset if we ever reach this.
	exit(0);
}
