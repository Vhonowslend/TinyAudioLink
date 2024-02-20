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

#include "nxp/imxrt1060/nvic.hpp"
#include <cinttypes>
#include <cstddef>
#include "arm/cm7.hpp"
#include "nxp/imxrt1060/iomuxc.hpp"
#include "reset.h"

extern std::size_t __stack_start;

[[gnu::used, gnu::section(".interruptVectorTable")]] nxp::imxrt1060::nvic::interrupt_vector_table_t nxp::imxrt1060::nvic::__interrupt_vector_table = {
	.initialStackPointer = &__stack_start,
	.reset               = &_start,
};

void nxp::imxrt1060::nvic::initialize()
{
	// Set Interrupt Vector Offset Register (VTOR)
	nxp::imxrt1060::iomuxc::gpr::GPR16 |= (size_t)&nvic::__interrupt_vector_table;
	arm::cm7::VTOR = (size_t)&__interrupt_vector_table;
}
