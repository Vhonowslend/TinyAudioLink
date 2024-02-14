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

#include "imxrt1060/bootdata.hpp"
#include "imxrt1060/imagevectortable.hpp"
#include "kinetis/flashloader.hpp"
#include "std/inttypes.h"

// Main Application
extern int main();

// Pre-definitions
void _start(void);

extern "C" {
	// Defined in Linker Script
	static uint32_t __flashImageLength;

	[[gnu::used, gnu::section(".flashLoader")]] static flashLoader_t __flashLoader = {
	};

	[[gnu::used, gnu::section(".bootData")]] static bootData_t __bootData = {
		.start  = (void*)0x6000000,
		.length = (uint32_t)&__flashImageLength,
	};

	[[gnu::used, gnu::section(".imageVectorTable")]] static imageVectorTable_t __imageVectorTable{
		.entryPoint = &_start,
		.bootData   = &__bootData,
		.self       = &__imageVectorTable,
	};
}

[[gnu::used, gnu::section(".startup")]] void _start(void)
{
	static_assert(sizeof(bootData_t) == 12, "Boot Data must be 12 bytes long.");
	static_assert(sizeof(imageVectorTable_t) == 32, "Image Vector Table must be 32 bytes long.");
	static_assert(sizeof(flashLoader_t) == 512, "Flash Loader must be 512 bytes long.");

	main();
}
