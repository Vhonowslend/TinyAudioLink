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

namespace nxp::imxrt1060::nvic {
	typedef void (*interrupt_function_t)();

	struct interrupt_vector_table_t {
		std::size_t*         initialStackPointer;
		interrupt_function_t reset;
		interrupt_function_t interrupts[240] = {0};
	};
	extern interrupt_vector_table_t __interrupt_vector_table;

	void initialize() noexcept;
} // namespace nxp::imxrt1060::nvic

#pragma pack(pop)
