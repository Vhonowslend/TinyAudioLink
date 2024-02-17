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

// This is critical, so ensure it's byte aligned.
#pragma pack(push, 1)

namespace arm::cm7 {
	static registerReadWrite<0xE000E008> ACTLR;
	static registerReadWrite<0xE000E010> SYST_CSR;
	static registerReadWrite<0xE000E014> SYST_RVR;
	static registerReadWrite<0xE000E018> SYST_CVR;
	static registerReadOnly<0xE000E01C>  SYST_CALIB;
	static registerReadWrite<0xE000ED00> CPUID;
	static registerReadWrite<0xE000ED04> ICSR;
	static registerReadWrite<0xE000ED08> VTOR;
} // namespace arm::cm7

#pragma pack(pop)
