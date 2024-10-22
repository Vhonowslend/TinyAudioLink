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

#include "arm/v7/fpu.hpp"
#include "arm/v7/v7.hpp"

[[gnu::section(".flashCode")]]
bool arm::v7::fpu::supported() noexcept
{
	size_t old = arm::v7::CPACR;
	arm::v7::CPACR |= (size_t(0b11) << 20) | (size_t(0b11) << 22);
	bool supported = enabled();
	arm::v7::CPACR = old;
	return supported;
}

[[gnu::section(".flashCode")]]
bool arm::v7::fpu::enabled() noexcept
{
	return (((size_t)arm::v7::CPACR >> 20) & 0b11) | (((size_t)arm::v7::CPACR >> 22) & 0b11) ? true : false;
}

[[gnu::section(".flashCode")]]
bool arm::v7::fpu::enable() noexcept
{
	arm::v7::CPACR |= (0b11 << 20) | (0b11 << 22);
	return enabled();
}

[[gnu::section(".flashCode")]]
void arm::v7::fpu::disable() noexcept
{
	arm::v7::CPACR = (size_t)arm::v7::CPACR & ~size_t((size_t(0b11) << 20) | (size_t(0b11) << 22));
}
