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

#pragma once
#include <cinttypes>
#include <cstddef>

// This is critical, so ensure it's byte aligned.
#pragma pack(push, 1)

extern "C" {
// Start of the Flash image.
static std::size_t __flashImageStart;
// Length of the entire flash image.
static std::size_t __flashImageLength;
}

/** Boot Data
 * - IMXRT1060RM_rev1_Processor_Manual.pdf: 8.7.1.2
 * 
 */
struct bootData_t {
	// 0x00 Absolute address of the image.
	std::size_t start = reinterpret_cast<std::size_t>(&__flashImageStart);
	// 0x04 Length of the image.
	std::size_t length = reinterpret_cast<std::size_t>(&__flashImageLength);
	// 0x08 Plugin flags, see 8.8
	uint32_t plugin = 0; // Some official images have a value here.
};
static constexpr std::size_t bootData_sz = 0xC;

#pragma pack(pop)
