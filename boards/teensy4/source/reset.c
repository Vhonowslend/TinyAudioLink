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

#include <inttypes.h>
#include <stddef.h>
#include "board.h"
#include "boot.h"
#include "nxp/imxrt1060/imxrt1060.h"

extern size_t __flexram_bank_config; // FlexRAM Bank Configuration
extern size_t __stack_start; // Stack Address

[[gnu::used, gnu::naked, gnu::noreturn]]
SECTION_CODE_BOOT void _reset(void)
{
	// Set up FlexRAM properly.
	asm volatile("str %[val], %[gpr]" : [gpr] "=g"(__IMXRT1060_IOMUXC_GPR17) : [val] "r"(&__flexram_bank_config) : "memory");
	asm volatile(
		"ldr r0, %[gpr];"
		"orr %[val], r0;"
		"str %[val], %[gpr];"
		: [gpr] "=g"(__IMXRT1060_IOMUXC_GPR16)
		: [val] "r"(0x00000007)
		: "r0", "memory");

#ifdef USE_TEENSY_IVT
	// Before we call any standard function, we need to set up the stack pointer.
	asm volatile("mov sp, %[stack]" : : [stack] "r"(&__stack_start) : "memory");
#endif

	// Wait until everything is synchronized again.
	asm volatile("isb" :::);
	asm volatile("dsb" :::);
	asm volatile("dmb" :::);

	// Once it's been set up, we can Branch to the actual start function which can do more complication things.
	// It is important to use the 'B' instruction here instead of the 'BX', 'BL' or similar instructions,
	// as 'B' simply jumps instead of branching.
	asm volatile("b %P0" : : "i"(&_start));
}
