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

	template<std::intptr_t address>
	struct gpio_block {
		// gpio::state[sizeof(size_t)] Varies by IOMUXC mode, but either reads itself or the status of the signal.
		register_read_write<address + 0x00> data;
		// gpio::direction[sizeof(size_t)] Direction, see gpio::direction
		register_read_write<address + 0x04> direction;
		// gpio::state[sizeof(size_t)] Status of the Input Signal
		register_read<address + 0x08> status;
		// gpio::interrupt_edge[sizeof(size_t) / 2] Interrupt configuration for the first half.
		register_read_write<address + 0x0C> interrupt_cfg1;
		// gpio::interrupt_edge[sizeof(size_t) / 2] Interrupt configuration for the second half.
		register_read_write<address + 0x10> interrupt_cfg2;
		// gpio::state[sizeof(size_t)] Interrupt Mask (Disabled or Enabled)
		register_read_write<address + 0x14> interrupt_mask;
		// gpio::state[sizeof(size_t)] Interrupt Status, Write 1 to Clear
		register_read_write<address + 0x18> interrupt_status;
		// gpio::state[sizeof(size_t)] Interrupt Edge Select.
		// - If on, replaces interrupt_edge and triggers on all signal edges.
		// - If off, uses interrupt_edge instead.
		register_read_write<address + 0x1C> interrupt_edge_select;
		// Large undefined space, unclear what this is for.

		// gpio::state[sizeof(size_t)] Data Set, just sets the correspending bit in data to 1.
		register_write<address + 0x84> set;
		// gpio::state[sizeof(size_t)] Data Clear, just sets the correspending bit in data to 0.
		register_write<address + 0x88> clear;
		// gpio::state[sizeof(size_t)] Data Toggle, just flips the correspending bit if set to 1.
		register_write<address + 0x8C> toggle;
	};

	static gpio_block<0x401B8000> GPIO1;
	static gpio_block<0x401BC000> GPIO2;
	static gpio_block<0x401C0000> GPIO3;
	static gpio_block<0x401C4000> GPIO4;
	static gpio_block<0x400C0000> GPIO5;
	static gpio_block<0x42000000> GPIO6;
	static gpio_block<0x42004000> GPIO7;
	static gpio_block<0x42008000> GPIO8;
	static gpio_block<0x4200C000> GPIO9;
} // namespace nxp::imxrt1060::gpio
