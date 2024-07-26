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

#include "arm/v7/cache.hpp"
#include "arm/v7/v7.hpp"

[[gnu::section(".flashCode")]]
bool arm::v7::cache::data::enabled() noexcept
{
	return ((size_t)arm::v7::CCR) >> 16 & 0b1;
}

[[gnu::section(".flashCode")]]
void arm::v7::cache::data::invalidate() noexcept
{
	arm::v7::CSSELR = 0b0;

	// Block until data is synchronized.
	arm::v7::data_synchronization_barrier();

	size_t ccsidr         = arm::v7::CCSIDR;
	size_t cacheline      = ccsidr & 0x7;
	size_t cachelinewords = cacheline + 0x4;
	size_t numways        = (ccsidr >> 3) & 0x3FF;
	size_t numsets        = (ccsidr >> 13) & 0xFFFF;
	size_t bitoffset; // Didn't find a C equivalent, so direct call it is.
	asm volatile("clz %[o], %[i]" : [o] "=r"(bitoffset) : [i] "r"(numways) :);
	for (auto sets = numsets; sets > 0; sets--) {
		size_t r8 = sets << cachelinewords;
		for (auto ways = numways; ways > 0; ways--) {
			size_t r3      = (ways << bitoffset | r8);
			arm::v7::DCISW = r3;
		}
	}

	// Wait for synchronization.
	arm::v7::data_synchronization_barrier();
	arm::v7::instruction_synchronization_barrier();
}

[[gnu::section(".flashCode")]]
void arm::v7::cache::data::clean() noexcept
{
	arm::v7::CSSELR = 0b0;

	// Block until data is synchronized.
	arm::v7::data_synchronization_barrier();

	size_t ccsidr         = arm::v7::CCSIDR;
	size_t cacheline      = ccsidr & 0x7;
	size_t cachelinewords = cacheline + 0x4;
	size_t numways        = (ccsidr >> 3) & 0x3FF;
	size_t numsets        = (ccsidr >> 13) & 0xFFFF;
	size_t bitoffset; // Didn't find a C equivalent, so direct call it is.
	asm volatile("clz %[o], %[i]" : [o] "=r"(bitoffset) : [i] "r"(numways) :);
	for (auto sets = numsets; sets > 0; sets--) {
		size_t r8 = sets << cachelinewords;
		for (auto ways = numways; ways > 0; ways--) {
			size_t r3      = (ways << bitoffset | r8);
			arm::v7::DCCSW = r3;
		}
	}

	// Wait for synchronization.
	arm::v7::data_synchronization_barrier();
	arm::v7::instruction_synchronization_barrier();
}

[[gnu::section(".flashCode")]]
void arm::v7::cache::data::clean_invalidate() noexcept
{
	arm::v7::CSSELR = 0b0;

	// Block until data is synchronized.
	arm::v7::data_synchronization_barrier();

	size_t ccsidr         = arm::v7::CCSIDR;
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
			arm::v7::DCCISW = r3;
		}
	}

	// Wait for synchronization.
	arm::v7::data_synchronization_barrier();
	arm::v7::instruction_synchronization_barrier();
}

[[gnu::section(".flashCode")]]
void arm::v7::cache::data::flush() noexcept
{}

[[gnu::section(".flashCode")]]
void arm::v7::cache::data::enable() noexcept
{
	disable();
	clean_invalidate();

	arm::v7::CCR |= 0b1 << 16;

	// Wait for synchronization.
	arm::v7::data_synchronization_barrier();
	arm::v7::instruction_synchronization_barrier();
}

[[gnu::section(".flashCode")]]
void arm::v7::cache::data::disable() noexcept
{
	if (enabled()) {
		flush();

		arm::v7::CCR = arm::v7::CCR.operator size_t() & ~(size_t(0b1) << 16ul);

		// Wait for synchronization.
		arm::v7::data_synchronization_barrier();
		arm::v7::instruction_synchronization_barrier();
	}
}

[[gnu::section(".flashCode")]]
bool arm::v7::cache::instruction::enabled() noexcept
{
	return ((size_t)arm::v7::CCR) >> 17 & 0b1;
}

[[gnu::section(".flashCode")]]
void arm::v7::cache::instruction::invalidate() noexcept
{
	arm::v7::CSSELR  = 0b1;
	arm::v7::ICIALLU = 0;

	// Wait for synchronization.
	arm::v7::data_synchronization_barrier();
	arm::v7::instruction_synchronization_barrier();
}

[[gnu::section(".flashCode")]]
void arm::v7::cache::instruction::enable() noexcept
{
	invalidate(); // Trashes instruction cache, but we don't really care.
	arm::v7::CCR |= 0b1 << 17;

	// Wait for synchronization.
	arm::v7::data_synchronization_barrier();
	arm::v7::instruction_synchronization_barrier();
}

[[gnu::section(".flashCode")]]
void arm::v7::cache::instruction::disable() noexcept
{
	arm::v7::CCR = arm::v7::CCR.operator size_t() & ~(size_t(0b1) << 17ul);

	// Wait for synchronization.
	arm::v7::data_synchronization_barrier();
	arm::v7::instruction_synchronization_barrier();
}
