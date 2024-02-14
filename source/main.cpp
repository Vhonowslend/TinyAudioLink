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
#include "imxrt1060/gpio.hpp"

extern "C" [[gnu::used]]
int main()
{
	gpio::GPIO2.direction = 0xFFFFFFFF;
	gpio::GPIO2.data      = 0xFFFFFFFF;
	while (true) {
		gpio::GPIO2.dataToggle = 0xFFFFFFFF;

		for (std::size_t i = 0; i < 0x11E1A300; i++) {
			i++;
		}
	}
	return 0;
}
