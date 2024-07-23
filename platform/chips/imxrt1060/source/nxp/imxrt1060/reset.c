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

#include <arm/cm7/cm7.h>
#include <inttypes.h>
#include <stddef.h>
#include "nxp/imxrt1060/imxrt1060.h"

extern size_t __flexram_bank_config; // FlexRAM Bank Configuration
extern size_t __stack_start; // Stack Address
extern void   _start();

[[gnu::used, gnu::naked, gnu::noreturn, gnu::section(".flashCode")]]
void _reset(void)
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
	asm volatile("isb;dsb;dmb" ::: "memory");

	// Once it's been set up, we can Branch to the actual start function which can do more complication things.
	// It is important to use the 'B' instruction here instead of the 'BX', 'BL' or similar instructions,
	// as 'B' simply jumps instead of branching.
	asm volatile("b %P0" : : "i"(&_start));
}

[[gnu::used, gnu::naked, gnu::noreturn, gnu::section(".flashCode")]]
void _exit(int code)
{
	// Wait for memory to sychronize entirely.
	asm volatile("isb;dsb;dmb" ::: "memory");

	// Enable debug, and request a local reset.
	asm volatile(
		"str %[dhcsr_val], %[dhcsr];"
		"str %[aircr_val], %[aircr]"
		: [dhcsr] "=g"(__CORTEXM7_DHCSR), [aircr] "=g"(__CORTEXM7_AIRCR)
		: [dhcsr_val] "r"(0xA05F0001), [aircr_val] "r"(0b100)
		:);

	// Now just loop until it happens, we can't affect this anyway.
	asm volatile("_exitnop%=:;nop;B _exitnop%=" :::);
}

// This is just fucked up, but hey, can't do anything because libc++ AND libUnwind link against the FILE* handle. Which as you might guess, is useless.
void* stderr = 0;
