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

extern std::size_t  __flexramBankConfig; // FlexRAM Bank Configuration
extern std::size_t* __stackStart; // Stack Address

[[gnu::used, gnu::section(".bootData")]] static bootData_t __bootData = {};

[[gnu::used, gnu::section(".flashLoader")]] static flashLoader_t __flashLoader = {};

[[gnu::used, gnu::section(".imageVectorTable")]] static imageVectorTable_t __imageVectorTable = {
	.entryPoint = &_start,
	.bootData   = &__bootData,
	.self       = &__imageVectorTable,
};

[[gnu::used, gnu::section(".interruptVectorTable")]] static nvic::interruptVectorTable_t interruptVectorTable = {
	.initialStackPointer = __stackStart,
	.reset               = &_start,
};

extern "C" [[gnu::used, gnu::visibility("default"), gnu::noinline, gnu::noreturn]]
void _start_internal(void)
{
	// Initialize ITCM
	extern std::size_t __fastCodeLength; // Flash Fast Code End
	extern std::size_t __fastCodeAddress; // Flash Fast Code Address
	extern std::size_t __itcmStart; // ITCM Address
	boot_memcpy(&__itcmStart, &__fastCodeAddress, reinterpret_cast<std::size_t>(&__fastCodeLength));

	// Initialize DTCM
	extern std::size_t __fastDataLength; // Flash Fast Data End
	extern std::size_t __fastDataAddress; // Flash Fast Data Address
	extern std::size_t __dtcmStart; // DTCM Address
	boot_memcpy(&__dtcmStart, &__fastDataAddress, reinterpret_cast<std::size_t>(&__fastDataLength));

	// Zero BSS area
	extern std::size_t __bssStart; // BSS Start
	extern std::size_t __bssLength; // BSS End
	boot_memset(&__bssStart, 0x00, reinterpret_cast<std::size_t>(&__bssLength));

	// Initialize Internal Memory
	if (BOARD_IRAM_SIZE > 0) {
		extern std::size_t __board_iram_address;
		extern std::size_t __board_iram_length;
		boot_memcpy(&board_iram, &__board_iram_address, reinterpret_cast<std::size_t>(&__board_iram_length));
	}

	// Initialize External Memory
	if (BOARD_ERAM_SIZE > 0) {
		extern std::size_t __board_eram_address;
		extern std::size_t __board_eram_length;
		boot_memcpy(&board_eram, &__board_eram_address, reinterpret_cast<std::size_t>(&__board_eram_length));
	}

	// Ensure all data is present.
	__asm volatile("dsb" ::: "memory");

	main();

	__builtin_unreachable();
}

extern "C" [[gnu::used, gnu::section(".flashCode"), gnu::naked, gnu::noreturn]]
void _start(void) noexcept
{
	// We can't use our nice register wrappers here, so raw writes to register it is.
	// Eventually move some of this into DCD:
	// - We can do the whole FlexRAM setup in there.
	// - Can't do the stack pointer AFAIK.

	// Set up FlexRAM Bank Config
	__asm volatile("str %[val], %[gpr]" : [gpr] "=m"(iomuxc::gpr::rawGPR17) : [val] "r"(reinterpret_cast<std::size_t>(&__flexramBankConfig)) : "memory");
	//iomuxc::gpr::rawGPR17 = reinterpret_cast<std::size_t>(&__flexramBankConfig);

	// Do two things.
	// - Set FLEXRAM_BANK_CFG_SEL to 1
	// - Set CM7_INIT_VTOR to the same as VTOR.
	__asm volatile("str %[val], %[gpr]" : [gpr] "=m"(iomuxc::gpr::rawGPR16) : [val] "r"(0b001000000000000000000111) : "memory");
	//iomuxc::gpr::rawGPR16 = static_cast<std::size_t>(0b001000000000000000000111);

	// Set Interrupt Vector Offset
	// - [0:6] is Read As Zero (ignored)
	// - [7:31] is the actualy address.
	// Address must be... 128 byte aligned?
	__asm volatile(R"(
		str %[ivt], %[vtor]
	)"
				   : [vtor] "=m"(cm7::VTOR.ref)
				   : [ivt] "r"(&interruptVectorTable)
				   : "memory");

	// Do apparently nothing, but its needed or the chip just freezes.
	// - Reduce bias current by 30% on ACMP1, ACMP3.
	// - Increase bias current by 30% on ACMP1, ACMP3.
	__asm volatile("str %[val], %[gpr]" : [gpr] "=m"(iomuxc::gpr::rawGPR14) : [val] "r"(0b101010100000000000000000) : "memory");
	//iomuxc::gpr::GPR14 = static_cast<std::size_t>(0b101010100000000000000000);

	// Set Stack Pointer
	__asm volatile("mov sp, %0" : : "r"(&__stackStart));

	// Hand off control to actual code, since we now have a stack and memory.
	// - Do not use BX, since it sets a return address!
	__asm volatile("b %P0" : : "i"(&_start_internal));
	//_start_internal();
}
