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
#include <endian.h>
#include "arm/v7/nvic.hpp"
#include "nxp/imxrt1060/bootdata.hpp"
#include "nxp/imxrt1060/deviceconfigurationdata.hpp"
#include "nxp/nxp.hpp"

#ifndef NXP_IVT
#define NXP_IVT 0x41
#endif

namespace nxp::imxrt1060 {
	/** Image Vector Table 4.0/4.1
	 * - Mentioned here: https://forum.pjrc.com/index.php?threads/teensy-4-imagevectortable-not-matching-the-nxp-format.67562/#post-282356
	 * - Unclear where that user got the information from, since I could not find this documentation they are talking about.
	 * - IMXRT1060RM_rev3.pdf: §9.5.5 describes the behavior, but not why it works like this.
	 ** Image Vector Table 4.3
	 * - IMXRT1060RM_rev3.pdf: Chapter 9, Program image, Image and Vector Table and Boot Data
	 * - IMXRT1060RM_rev1_Processor_Manual.pdf: 8.7.1
	 */
	struct [[gnu::packed, gnu::aligned(1)]] image_vector_table_t {
		// 0x00 Header: Tag, Length, Version in one field.
		nxp::header_t header = {
			.tag       = 0xD1,
			.length    = htobe16(sizeof(nxp::imxrt1060::image_vector_table_t)),
			.parameter = NXP_IVT,
		};
#if NXP_IVT == 0x43
		// Teensy 4.x ships with a different version (4.3) that jumps straight to code.
		// 0x04 Entry: Absolute address of the first function
		void (*entryPoint)() = nullptr;
#else
		// 0x04 Entry: Absolute address of the interrupt vector table
		void* entryPoint = nullptr;
#endif
		// 0x08 Reserved, must be zero.
		uint32_t __reserved1 = 0;
		// 0x0C Device Configuration Data: Absolute address but optional, so it's NULL.
		nxp::imxrt1060::device_configuration_data::data_t const* dcd = nullptr;
		// 0x10 Boot Data: Absolute address of the boot data.
		nxp::imxrt1060::boot_data_t const* bootData = nullptr;
		// 0x14 Image Vector Table: The address of this structure.
		nxp::imxrt1060::image_vector_table_t const* self = nullptr;
		// 0x18 Command Sequence File: See High-Assurance Boot for details. Must be NULL if not performing HAB.
		void const* csf = nullptr;
		// 0x1C Reserved, must be zero.
		uint32_t __reserved2 = 0;
	}; // 0x20

	static_assert(sizeof(nxp::imxrt1060::image_vector_table_t) == 32, "Image Vector Table must be 32 bytes long.");
} // namespace nxp::imxrt1060
