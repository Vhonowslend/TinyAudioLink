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

#include "imagevectortable.hpp"
#include "board.h"
#include "nxp/imxrt1060/imxrt1060.h"

extern std::size_t __flexram_bank_config; // FlexRAM Bank Configuration

namespace dcd = nxp::imxrt1060::device_configuration_data;

struct teensy_dcd {
	// 0x00
	dcd::data_t header = {
		.header{
			.tag       = 0xD2,
			.length    = htobe16(sizeof(teensy_dcd)),
			.parameter = 0x41,
		},
	};

	/** Configure FlexRAM banks as preferred.
	 */
	dcd::write::command_t write_flexram_configuration = {
		.header{
			.parameter{
				.width = dcd::width::LONG,
			},
		},
		.address = (std::intptr_t*)&__IMXRT1060_IOMUXC_GPR17,
		.value_or_mask{
			.pointer = &__flexram_bank_config,
		},
	};

	/** 0x10 Enable reading FlexRAM configuration from GPR17
	 * 
	 */
	dcd::write::command_t enable_flexram_configuration = {
		.header{
			.parameter{
				.width = dcd::width::LONG,
				.set   = true,
				.mask  = true,
			},
		},
		.address = (std::intptr_t*)&__IMXRT1060_IOMUXC_GPR16,
		.value_or_mask{
			.number = 0x7,
		},
	};
};

[[gnu::used, gnu::section(".dcd")]] constexpr teensy_dcd teensyDCD;

[[gnu::used, gnu::section(".imageVectorTable")]] nxp::imxrt1060::image_vector_table_t nxp::imxrt1060::__image_vector_table = {
#ifdef USE_TEENSY_IVT
	.entryPoint = &_start,
#endif
	.dcd      = reinterpret_cast<decltype(nxp::imxrt1060::image_vector_table_t::dcd)>(&teensyDCD),
	.bootData = &__boot_data,
	.self     = &__image_vector_table,
};
