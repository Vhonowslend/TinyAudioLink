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

#include "bootloader.hpp"
#include <cinttypes>
#include <cstddef>
#include <cstring>
#include "board.h"
#include "imxrt1060/bootdata.hpp"
#include "imxrt1060/cm7.hpp"
#include "imxrt1060/gpio.hpp"
#include "imxrt1060/imagevectortable.hpp"
#include "imxrt1060/iomuxc.hpp"
#include "imxrt1060/nvic.hpp"
#include "kinetis/flashloader.hpp"

// Main Application
extern "C" int main();

extern std::size_t __flexramBankConfig; // FlexRAM Bank Configuration
extern std::size_t __stackStart; // Stack Address

[[gnu::used, gnu::section(".bootData")]] static bootData_t __bootData = {};

[[gnu::used, gnu::section(".flashLoader")]] static flashLoader_t __flashLoader = {};

[[gnu::used, gnu::section(".interruptVectorTable")]] nvic::interruptVectorTable_t __interruptVectorTable = {
	.initialStackPointer = &__stackStart,
	.reset               = &_start,
};

[[gnu::used, gnu::section(".imageVectorTable")]] static imageVectorTable_t __imageVectorTable = {
	//	.entryPoint = &_start,
	.bootData = &__bootData,
	.self     = &__imageVectorTable,
};

extern "C" SECTION_CODE_BOOT [[gnu::used, gnu::visibility("default"), gnu::noinline, gnu::noreturn]]
void _start_internal(void)
{
	// Do apparently nothing, but its needed or the chip just freezes.
	// - Reduce bias current by 30% on ACMP1, ACMP3.
	// - Increase bias current by 30% on ACMP1, ACMP3.
	iomuxc::gpr::GPR14 = 0b101010100000000000000000;

	// Set Interrupt Vector Offset Register (VTOR)
	iomuxc::gpr::GPR16 |= (size_t)&__interruptVectorTable;
	cm7::VTOR = (size_t)&__interruptVectorTable;

	{ // Initialize ITCM
		extern std::size_t __fastCodeLength; // Flash Fast Code End
		extern std::size_t __fastCodeAddress; // Flash Fast Code Address
		extern std::size_t __itcmStart; // ITCM Address
		boot_memcpy(&__itcmStart, &__fastCodeAddress, reinterpret_cast<std::size_t>(&__fastCodeLength));
	}

	{ // Initialize DTCM
		extern std::size_t __fastDataLength; // Flash Fast Data End
		extern std::size_t __fastDataAddress; // Flash Fast Data Address
		extern std::size_t __dtcmStart; // DTCM Address
		boot_memcpy(&__dtcmStart, &__fastDataAddress, reinterpret_cast<std::size_t>(&__fastDataLength));
	}

	// Wait until everything is synchronized again.
	asm volatile(R"(
		isb
		dsb
		dmb
	)" ::
					 : "memory");

	if (false) { // Zero BSS area
		extern std::size_t __bssStart; // BSS Start
		extern std::size_t __bssLength; // BSS End
		boot_memset(&__bssStart, 0x00, reinterpret_cast<std::size_t>(&__bssLength));
	}

	// Initialize Internal Memory
	if (BOARD_IRAM_SIZE > 0 && false) {
		extern std::size_t __board_iram_address;
		extern std::size_t __board_iram_length;
		boot_memcpy(BOARD_IRAM, &__board_iram_address, reinterpret_cast<std::size_t>(&__board_iram_length));
	}

	// Initialize External Memory
	if (BOARD_ERAM_SIZE > 0 && false) {
		extern std::size_t __board_eram_address;
		extern std::size_t __board_eram_length;
		boot_memcpy(BOARD_ERAM, &__board_eram_address, reinterpret_cast<std::size_t>(&__board_eram_length));
	}

	// Wait until everything is synchronized again.
	asm volatile(R"(
		isb
		dsb
		dmb
	)" ::
					 : "memory");

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

	__builtin_unreachable();
}

extern "C" SECTION_CODE_BOOT [[gnu::used, gnu::naked, gnu::noreturn]]
void _start(void) noexcept
{
	// Set up FlexRAM properly.
	asm volatile("str %[val], %[gpr]" : [gpr] "=m"(iomuxc::gpr::GPR17.ref) : [val] "r"(&__flexramBankConfig) : "memory");
	asm volatile("str %[val], %[gpr]" : [gpr] "=m"(iomuxc::gpr::GPR16.ref) : [val] "r"(0x00200007) : "memory");

	// FlexRAM may take a bit to "warm up", so we purposefully wait 1 cycle per bank here.
	asm volatile(R"(
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop
		nop)" ::
					 :);

#ifdef USE_TEENSY_IVT
	// Before we call any standard function, we need to set up the stack pointer.
	asm volatile("mov sp, %[stack]" : : [stack] "r"(&__stackStart) : "memory");
#endif

	// Wait until everything is synchronized again.
	asm volatile(R"(
		isb
		dsb
		dmb
	)" ::
					 : "memory");

	// Once it's been set up, we can Branch to the actual start function which can do more complication things. It is important to use the 'B' instruction here instead of the 'BX', 'BL' or similar instructions, as 'B' simply jumps instead of branching.
	asm volatile("b %P0" : : "i"(&_start_internal));
}
