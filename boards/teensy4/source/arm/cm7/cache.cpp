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

#include "arm/cm7/cache.hpp"
#include "arm/cm7/cm7.hpp"
#include "board.h"

SECTION_CODE_BOOT
bool arm::cm7::cache::data::enabled()
{
	return ((size_t)arm::cm7::CCR) >> 16 & 0b1;
}

SECTION_CODE_BOOT
void arm::cm7::cache::data::invalidate()
{
	arm::cm7::CSSELR = 0b0;
	asm volatile("dsb"); // Block until data is synchronized.
	size_t ccsidr         = arm::cm7::CCSIDR;
	size_t cacheline      = ccsidr & 0x7;
	size_t cachelinewords = cacheline + 0x4;
	size_t numways        = (ccsidr >> 3) & 0x3FF;
	size_t numsets        = (ccsidr >> 13) & 0xFFFF;
	size_t bitoffset; // Didn't find a C equivalent, so direct call it is.
	asm volatile("clz %[o], %[i]" : [o] "=r"(bitoffset) : [i] "r"(numways) :);
	for (auto sets = numsets; sets > 0; sets--) {
		size_t r8 = sets << cachelinewords;
		for (auto ways = numways; ways > 0; ways--) {
			size_t r3       = (ways << bitoffset | r8);
			arm::cm7::DCISW = r3;
		}
	}
	asm volatile("dsb;isb;");
}

SECTION_CODE_BOOT
void arm::cm7::cache::data::clean()
{
	arm::cm7::CSSELR = 0b0;
	asm volatile("dsb"); // Block until data is synchronized.
	size_t ccsidr         = arm::cm7::CCSIDR;
	size_t cacheline      = ccsidr & 0x7;
	size_t cachelinewords = cacheline + 0x4;
	size_t numways        = (ccsidr >> 3) & 0x3FF;
	size_t numsets        = (ccsidr >> 13) & 0xFFFF;
	size_t bitoffset; // Didn't find a C equivalent, so direct call it is.
	asm volatile("clz %[o], %[i]" : [o] "=r"(bitoffset) : [i] "r"(numways) :);
	for (auto sets = numsets; sets > 0; sets--) {
		size_t r8 = sets << cachelinewords;
		for (auto ways = numways; ways > 0; ways--) {
			size_t r3       = (ways << bitoffset | r8);
			arm::cm7::DCCSW = r3;
		}
	}
	asm volatile("dsb;isb;");
}

SECTION_CODE_BOOT
void arm::cm7::cache::data::clean_invalidate()
{
	arm::cm7::CSSELR = 0b0;
	asm volatile("dsb"); // Block until data is synchronized.
	size_t ccsidr         = arm::cm7::CCSIDR;
	size_t cacheline      = ccsidr & 0x7;
	size_t cachelinewords = cacheline + 0x4;
	size_t numways        = (ccsidr >> 3) & 0x3FF;
	size_t numsets        = (ccsidr >> 13) & 0xFFFF;
	size_t bitoffset; // Didn't find a C equivalent, so direct call it is.
	asm volatile("clz %[o], %[i]" : [o] "=r"(bitoffset) : [i] "r"(numways) :);
	for (auto sets = numsets; sets > 0; sets--) {
		size_t r8 = sets << cachelinewords;
		for (auto ways = numways; ways > 0; ways--) {
			size_t r3        = (ways << bitoffset | r8);
			arm::cm7::DCCISW = r3;
		}
	}
	asm volatile("dsb;isb;");
}

SECTION_CODE_BOOT
void arm::cm7::cache::data::flush() {}

SECTION_CODE_BOOT
void arm::cm7::cache::data::enable()
{
	disable();
	clean_invalidate();

	arm::cm7::CCR |= 0b1 << 16;
	asm volatile("dsb;isb;");
}

SECTION_CODE_BOOT
void arm::cm7::cache::data::disable()
{
	if (enabled()) {
		flush();

		arm::cm7::CCR = arm::cm7::CCR.operator size_t() & ~(size_t(0b1) << 16ul);
		asm volatile("dsb;isb;");
	}
}

SECTION_CODE_BOOT
bool arm::cm7::cache::instruction::enabled()
{
	return ((size_t)arm::cm7::CCR) >> 17 & 0b1;
}

SECTION_CODE_BOOT
void arm::cm7::cache::instruction::invalidate()
{
	arm::cm7::CSSELR  = 0b1;
	arm::cm7::ICIALLU = 0;
	asm volatile("dsb;isb;");
}

SECTION_CODE_BOOT
void arm::cm7::cache::instruction::enable()
{
	invalidate(); // Trashes instruction cache, but we don't really care.
	arm::cm7::CCR |= 0b1 << 17;
	asm volatile("dsb;isb;");
}

SECTION_CODE_BOOT
void arm::cm7::cache::instruction::disable()
{
	arm::cm7::CCR = arm::cm7::CCR.operator size_t() & ~(size_t(0b1) << 17ul);
	asm volatile("dsb;isb;");
}
