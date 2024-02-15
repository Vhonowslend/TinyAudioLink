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

#include <cinttypes>
#include <cstddef>
#include "imxrt1060/bootdata.hpp"
#include "imxrt1060/gpio.hpp"
#include "imxrt1060/imagevectortable.hpp"
#include "imxrt1060/iomuxc.hpp"
#include "kinetis/flashloader.hpp"

extern "C" [[gnu::section(".startup")]]
void* flash_memcpy(void* dest, const void* src, std::size_t count)
{
#include "memcpy.impl"
}

extern "C" [[gnu::section(".startup")]]
void* flash_memset(void* dest, uint8_t value, std::size_t count)
{
#include "memset.impl"
}

// Main Application
extern "C" int main();

extern std::size_t __flexramBankConfig; // FlexRAM Bank Configuration
extern std::size_t __stackStart; // Stack Address
extern std::size_t __itcmStart; // ITCM Address
extern std::size_t __dtcmStart; // DTCM Address
extern std::size_t __fastCodeStart; // Flash Fast Code Start
extern std::size_t __fastCodeEnd; // Flash Fast Code End
extern std::size_t __fastCodeLength; // Flash Fast Code End
extern std::size_t __fastCodeAddress; // Flash Fast Code Address
extern std::size_t __fastDataStart; // Flash Fast Data Start
extern std::size_t __fastDataEnd; // Flash Fast Data End
extern std::size_t __fastDataLength; // Flash Fast Data End
extern std::size_t __fastDataAddress; // Flash Fast Data Address
extern std::size_t __bssStart; // BSS Start
extern std::size_t __bssEnd; // BSS End
extern std::size_t __bssLength; // BSS End

// Pre-definitions
extern "C" void _start(void);
extern "C" void _start_internal(void);

[[gnu::used, gnu::section(".bootData")]] static bootData_t __bootData = {};

[[gnu::used, gnu::section(".flashLoader")]] static flashLoader_t __flashLoader = {};

[[gnu::used, gnu::section(".imageVectorTable")]] static imageVectorTable_t __imageVectorTable{
	.entryPoint = &_start,
	.bootData   = &__bootData,
	.self       = &__imageVectorTable,
};

extern "C" [[gnu::used, gnu::section(".startup"), gnu::visibility("default"), gnu::naked, gnu::noreturn]]
void _start(void)
{
	// We can't use our nice register wrappers here, so raw writes to register it is.
	// Eventually move some of this into DCD:
	// - We can do the whole FlexRAM setup in there.
	// - Can't do the stack pointer AFAIK.

	// Ensure all data is present.
	__asm volatile("dsb" ::: "memory");

	// Set up FlexRAM Bank Config
	__asm volatile("mov %P0, %1" : : "r"(iomuxc::gpr::rawGPR17), "r"(reinterpret_cast<std::size_t>(&__flexramBankConfig)) : "memory");
	//iomuxc::gpr::rawGPR17 = reinterpret_cast<std::size_t>(&__flexramBankConfig);

	// Do two things.
	// - Set FLEXRAM_BANK_CFG_SEL to 1
	// - Set CM7_INIT_VTOR to 7.
	__asm volatile("mov %P0, %1" : : "r"(iomuxc::gpr::rawGPR16), "r"(0b001000000000000000000111) : "memory");
	//iomuxc::gpr::rawGPR16 = static_cast<std::size_t>(0b001000000000000000000111);

	// Do apparently nothing, but its needed or the chip just freezes.
	// - Reduce bias current by 30% on ACMP1, ACMP3.
	// - Increase bias current by 30% on ACMP1, ACMP3.
	__asm volatile("mov %P0, %1" : : "r"(iomuxc::gpr::rawGPR14), "r"(0b101010100000000000000000) : "memory");
	//iomuxc::gpr::GPR14 = static_cast<std::size_t>(0b101010100000000000000000);

	// Set Stack Pointer
	__asm volatile("mov sp, %0" : : "r"(&__stackStart));

	// Hand off control to actual code, since we now have a stack and memory.
	__asm volatile("b %P0" : : "i"(&_start_internal));
	//_start_internal();
}

extern "C" [[gnu::used, gnu::section(".startup"), gnu::visibility("default"), gnu::noinline, gnu::noreturn]]
void _start_internal(void)
{
	static_assert(sizeof(bootData_t) == bootData_sz, "Boot Data must be 12 bytes long.");
	static_assert(sizeof(imageVectorTable_t) == imageVectorTable_sz, "Image Vector Table must be 32 bytes long.");
	static_assert(sizeof(flashLoader_t) == falshLoader_sz, "Flash Loader must be 512 bytes long.");

	// Need to do these from Flash, since ITCM, DTCM and BSS are not yet initialized.
	flash_memcpy(&__itcmStart, &__fastCodeStart, reinterpret_cast<std::size_t>(&__fastCodeLength));
	flash_memcpy(&__dtcmStart, &__fastDataStart, reinterpret_cast<std::size_t>(&__fastDataLength));
	flash_memset(&__bssStart, 0x00, reinterpret_cast<std::size_t>(&__bssLength));

	// Ensure all data is present.
	__asm volatile("dsb" ::: "memory");

	main();

	__builtin_unreachable();
}
