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
#include "kinetis/flashloader.hpp"

// Main Application
extern "C" int main();

// Pre-definitions
void _start(void);

extern "C" {
[[gnu::used, gnu::section(".flashLoader")]] static flashLoader_t __flashLoader = {};

[[gnu::used, gnu::section(".bootData")]] static bootData_t __bootData = {};

[[gnu::used, gnu::section(".imageVectorTable")]] static imageVectorTable_t __imageVectorTable{
	.entryPoint = &_start,
	.bootData   = &__bootData,
	.self       = &__imageVectorTable,
};
}

[[gnu::used, gnu::section(".startup"), gnu::visibility("default")]] void _start(void)
{
	static_assert(sizeof(bootData_t) == 12, "Boot Data must be 12 bytes long.");
	static_assert(sizeof(imageVectorTable_t) == 32, "Image Vector Table must be 32 bytes long.");
	static_assert(sizeof(flashLoader_t) == 512, "Flash Loader must be 512 bytes long.");

	while (true) {
		gpio::GPIO2.direction  = static_cast<std::size_t>(gpio::GPIO2.direction) | static_cast<std::size_t>(gpio::direction::Output) << 3;
		gpio::GPIO2.dataToggle = static_cast<std::size_t>(gpio::state::On) << 3;

		main();

		for (auto i = 0; i < 0x7FFFFFFF; i++) {
			i++;
		}
	}
}
