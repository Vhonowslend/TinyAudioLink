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

namespace cm7 {
	static volatile std::size_t&        rawACTLR = *reinterpret_cast<std::size_t*>(0xE00E008);
	static registerReadWrite<0xE00E008> ACTLR;

	static volatile std::size_t&         rawSYST_CSR = *reinterpret_cast<std::size_t*>(0xE000E010);
	static registerReadWrite<0xE000E010> SYST_CSR;
	static volatile std::size_t&         rawSYST_RVR = *reinterpret_cast<std::size_t*>(0xE000E014);
	static registerReadWrite<0xE000E014> SYST_RVR;
	static volatile std::size_t&         rawSYST_CVR = *reinterpret_cast<std::size_t*>(0xE000E018);
	static registerReadWrite<0xE000E018> SYST_CVR;
	static volatile std::size_t const&   rawSYST_CALIB = *reinterpret_cast<std::size_t*>(0xE000E01C);
	static registerReadOnly<0xE000E01C>  SYST_CALIB;

	static volatile std::size_t&         rawCPUID = *reinterpret_cast<std::size_t*>(0xE000ED00);
	static registerReadWrite<0xE000ED00> CPUID;

	static volatile std::size_t&         rawICSR = *reinterpret_cast<std::size_t*>(0xE000ED04);
	static registerReadWrite<0xE000ED04> ICSR;

	static volatile std::size_t&         rawVTOR = *reinterpret_cast<std::size_t*>(0xE000ED08);
	static registerReadWrite<0xE000ED08> VTOR;

	/*	static volatile std::size_t&         rawSYST_CSR = *reinterpret_cast<std::size_t*>(0xE000E010);
	static registerReadWrite<0xE000E010> SYST_CSR;

	static volatile std::size_t&         rawSYST_CSR = *reinterpret_cast<std::size_t*>(0xE000E010);
	static registerReadWrite<0xE000E010> SYST_CSR;

	static volatile std::size_t&         rawSYST_CSR = *reinterpret_cast<std::size_t*>(0xE000E010);
	static registerReadWrite<0xE000E010> SYST_CSR;*/

} // namespace cm7

#pragma pack(pop)
