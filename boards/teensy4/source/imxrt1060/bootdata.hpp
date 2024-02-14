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
#ifndef TEENSY41_BOOTDATA_H
#define TEENSY41_BOOTDATA_H

// This is critical, so ensure it's byte aligned.
#pragma pack(push, 1)

#include <cinttypes>

extern "C" {
// Start of the Flash image.
static uint32_t __flashImageStart;
// Length of the entire flash image.
static uint32_t __flashImageLength;
}

/** Boot Data
 * - IMXRT1060RM_rev1_Processor_Manual.pdf: 8.7.1.2
 * 
 */
struct bootData_t {
	// Absolute address of the image.
	void* start = (void*)&__flashImageStart;
	// Length of the image.
	uint32_t length = (uint32_t)&__flashImageLength;
	// Plugin flags, see 8.8
	uint32_t plugin = 0;
};

#pragma pack(pop)
#endif
