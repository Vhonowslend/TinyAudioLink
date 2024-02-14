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
#ifndef TEENSY41_IMAGEVECTORTABLE_H
#define TEENSY41_IMAGEVECTORTABLE_H

#include <inttypes.h>
#include "bootdata.hpp"

// This is critical, so ensure it's byte aligned.
#pragma pack(push, 1)

/** Image Vector Table 
 * - IMXRT1060RM_rev3.pdf: Chapter 9, Program image, Image and Vector Table and Boot Data
 * - IMXRT1060RM_rev1_Processor_Manual.pdf: 8.7.1
 */
struct imageVectorTable_t;
struct imageVectorTable_t {
	// Big Endian Header: Tag, Length, Version in one field.
	// - Should end up as 0x412000D1.
	struct header_t {
		uint8_t  version = 0x41;
		uint16_t length  = sizeof(imageVectorTable_t);
		uint8_t  tag     = 0xD1;
	} header;
	// Entry: Absolute address of the first instruction?
	void (*entryPoint)() = nullptr;
	// Reserved, must be zero.
	uint32_t __reserved1 = 0;
	// Device Configuration Data: Absolute address but optional, so it's NULL.
	void* dcd = nullptr;
	// Boot Data: Absolute address of the boot data.
	bootData_t* bootData = nullptr;
	// Image Vector Table: The address of this structure.
	imageVectorTable_t* self = nullptr;
	// Command Sequence File: See High-Assurance Boot for details. Must be NULL if not performing HAB.
	void* csf = nullptr;
	// Reserved, must be zero.
	uint32_t __reserved2 = 0;
};

#pragma pack(pop)
#endif
