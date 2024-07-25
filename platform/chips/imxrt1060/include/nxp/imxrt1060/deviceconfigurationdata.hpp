// TinyAudioLink - Seamlessly transfer Audio between USB capable devices
// Copyright (C) 2024 Michael Fabian 'Xaymar' Dirks
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
#include <endian.h>
#import "cinttypes"
#import "cstddef"
#include "nxp/nxp.hpp"

namespace nxp::imxrt1060::device_configuration_data {
	enum class width : uint8_t {
		BYTE  = 1,
		SHORT = 2,
		LONG  = 4,
	};

	struct [[gnu::packed, gnu::aligned(1)]] command_header_t {
		uint8_t  tag;
		uint16_t length;

		union {
			uint8_t value;

			struct {
				width   width : 3;
				uint8_t set : 1;
				uint8_t mask : 1;
				uint8_t __ignored : 3;
			};
		} parameter;
	};

	struct [[gnu::packed, gnu::aligned(1)]] write_t {
		command_header_t header{
			.tag       = 0xCC,
			.length    = htobe16(sizeof(write_t)),
			.parameter = {0},
		};
		std::intptr_t* address = 0;

		union {
			size_t  number = 0;
			size_t* pointer;
		} value_or_mask;
	}; // namespace write

	struct [[gnu::packed, gnu::aligned(1)]] check_command_t {
		command_header_t header{
			.tag       = 0xCF,
			.length    = htobe16(sizeof(check_command_t)),
			.parameter = {0},
		};
		std::intptr_t* address = 0;

		union {
			size_t  number = 0;
			size_t* pointer;
		} mask;
	};

	struct limit_command_t {
		check_command_t command{
			.header =
				{
					.length = htobe16(sizeof(limit_command_t)),
				},
		};
		size_t count = 1;
	};

	struct [[gnu::packed, gnu::aligned(1)]] nop_t {
		command_header_t header{
			.tag       = 0xC0,
			.length    = htobe16(sizeof(nop_t)),
			.parameter = {0},
		};
	};

	struct [[gnu::packed, gnu::aligned(1)]] data_t {
		header_t header{
			.tag       = 0xD2,
			.length    = htobe16(sizeof(data_t)), // Adjust later.
			.parameter = 0x41,
		};
		// Add commands after here.
	};
} // namespace nxp::imxrt1060::device_configuration_data
