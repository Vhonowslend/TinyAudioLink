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
#include "register.hpp"

namespace nxp::imxrt1060::gpio {
	enum class direction : bool {
		Input  = false,
		Output = true,
	};

	enum class state : bool {
		Off = false,
		On  = true,
	};

	enum class interrupt_edge_cfg : uint8_t {
		Low         = 0b00,
		High        = 0b01,
		RisingEdge  = 0b10,
		FallingEdge = 0b11,
	};
} // namespace nxp::imxrt1060::gpio
