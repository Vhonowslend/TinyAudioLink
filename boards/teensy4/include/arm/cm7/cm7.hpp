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
	static register_read_write<0xE000E008> ACTLR;

	static register_unknown<0xE000E00C> __reserved0;

	static register_read_write<0xE000E010> SYST_CSR;
	static register_read_write<0xE000E014> SYST_RVR;
	static register_read_write<0xE000E018> SYST_CVR;
	static register_read<0xE000E01C>       SYST_CALIB;

	static register_read<0xE000ED00> CPUID;

	static register_read_write<0xE000ED04> ICSR; // May be ReadOnly
	static register_read_write<0xE000ED08> VTOR;

	/** Application Interrupt and Reset Control Register
	 * - [31...16] VECTKEY/VECTKEYSTAT. Always is 0xFA05 on read, and writes that aren't 0x05FA are ignored entirely.
	 * - [15] Memory Endianness (Read Only, obviously).
	 *   - 0 Little Endian
	 *   - 1 Big Endian
	 * - [14...11] Reserved.
	 * - [10..8] Priority grouping. Unsure what this does.
	 * - [7...3] Reserved.
	 * - [2] System Request Request. Set to 1 to request a reset.
	 * - [1] Write 1 to clear all configuration for exceptions, including ISPR. Should not be written to outside of debug mode.
	 * - [0] Write 1 to reset the system. Again, should only be done in debug mode.
	 */
	static register_read_write<0xE000ED0C> AIRCR;

	/** System Control Register
	 * - [31...5] Reserved
	 * - [4] Should interrupt transitions be considered wakeup events?
	 * - [3] Reserved
	 * - [2] Is the sleep mode considered deep sleep and will take longer?
	 * - [1] Should a return from ISR to the base level enter sleep?
	 * - [0] Reserved
	 */
	static register_read_write<0xE000ED10> SCR;

	/** Configuration and Control Register (Bitfield)
	 * - [31...19] Reserved
	 * - [18] Branch Predictor Enabled?
	 * - [17] Instruction Cache Enabled?
	 * - [16] Data Cache Enabled?
	 * - [15...10] Reserved
	 * - [9] Stack Alignment
	 *   - 0: Stack is 4-byte aligned
	 *   - 1: Stack is 8-byte aligned (recommended by ARM)
	 * - [8]
	 * - [7...5] Reserved
	 * - [4] Enable trapping divides by zero?
	 * - [3] Enable trapping unaligned word or halfword access?
	 * - [2] Reserved
	 * - [1] Can unprivileged software access STIR?
	 * - [0] Can processor enter thread mode with exceptions enabled?
	 *   - 0 No, and it will cause another exception if you do.
	 *   - 1 Yes, see documentation DDI0403EE_arm_v7m_ref_manual.pdf.
	 */
	static register_read_write<0xE000ED14> CCR;

	static register_read_write<0xE000ED18> SHPR1;
	static register_read_write<0xE000ED1C> SHPR2;
	static register_read_write<0xE000ED20> SHPR3;
	static register_read_write<0xE000ED24> SHCSR;

	static register_read_write<0xE000ED28> CFSR;
	static register_read_write<0xE000ED2C> HFSR;
	static register_read_write<0xE000ED30> DFSR;
	static register_read_write<0xE000ED34> MMFAR;
	static register_read_write<0xE000ED38> BFAR;

	static register_read<0xE000ED40> ID_PFR0;
	static register_read<0xE000ED44> ID_PFR1;

	static register_read<0xE000ED48> ID_DFR0;

	static register_read<0xE000ED4C> ID_AFR0;

	static register_read<0xE000ED50> ID_MMFR0;
	static register_read<0xE000ED54> ID_MMFR1;
	static register_read<0xE000ED58> ID_MMFR2;
	static register_read<0xE000ED5C> ID_MMFR3;

	static register_read<0xE000ED60> ID_ISAR0;
	static register_read<0xE000ED64> ID_ISAR1;
	static register_read<0xE000ED68> ID_ISAR2;
	static register_read<0xE000ED6C> ID_ISAR3;
	static register_read<0xE000ED70> ID_ISAR4;

	static register_read<0xE000ED78>       CLIDR;
	static register_read<0xE000ED7C>       CTR;
	static register_read<0xE000ED80>       CCSIDR;
	static register_read_write<0xE000ED84> CSSELR;

	/** Coprocessor access Control Register
	 * - [31...24] Reserved
	 * - [23...22] CP11
	 * 	 - Combine with CP10 to enable the Floating Point Unit, if present.
	 * - [21...20] CP10
	 * 	 - Combine with CP11 to enable the Floating Point Unit, if present.
	 * - [19...16] Reserved
	 * - [15...14] CP7
	 * - [13...12] CP6
	 * - [11...10] CP5
	 * - [9...8] CP4
	 * - [7...6] CP3
	 * - [5...4] CP2
	 * - [3...2] CP1
	 * - [1...0] CP0
	 * 
	 * Possible values
	 * - 0b00 Disable all access, and trigger a UsageFault.
	 * - 0b01 Access for privileged processes only. Triggers a UsageFault for non-privileged access.
	 * - 0b10 Reserved (Probably access for non-privileged only, which makes no sense).
	 * - 0b11 Full Access.
	 */
	static register_read_write<0xE000ED88> CPACR;

	static register_write<0xE000EF00> STIR;

	static register_write<0xE000EF50>   ICIALLU;
	static register_unknown<0xE000EF54> __reserved1;
	static register_write<0xE000EF58>   ICIMVAU;

	static register_write<0xE000EF5C> DCIMVAC;
	static register_write<0xE000EF60> DCISW;
	static register_write<0xE000EF64> DCCMVAU;
	static register_write<0xE000EF68> DCCMVAC;
	static register_write<0xE000EF6C> DCCSW;
	static register_write<0xE000EF70> DCCIMVAC;
	static register_write<0xE000EF74> DCCISW;

	static register_write<0xE000EF78>   BPIALL; // "Not implemented"
	static register_unknown<0xE000EF7C> __reserved2;
	static register_unknown<0xE000EF80> __reserved3;

	static register_read_write<0xE000EF90> ITCMCR;
	static register_read_write<0xE000EF94> DTCMCR;
	static register_read_write<0xE000EF98> AHBPCR;
	static register_read_write<0xE000EF9C> CACR;
	static register_read_write<0xE000EFA0> AHBSCR;
	static register_unknown<0xE000EFA4>    __reserved4;
	static register_read_write<0xE000EFA8> ABFSR;

	static register_read_write<0xE000EFB0> IEBR0;
	static register_read_write<0xE000EFB4> IEBR1;

	static register_read_write<0xE000EFB8> DEBR0;
	static register_read_write<0xE000EFBC> DEBR1;

	static register_unknown<0xE000EFD0> PID4;
	static register_unknown<0xE000EFD4> PID5;
	static register_unknown<0xE000EFD8> PID6;
	static register_unknown<0xE000EFDC> PID7;
	static register_unknown<0xE000EFE0> PID0;
	static register_unknown<0xE000EFE4> PID1;
	static register_unknown<0xE000EFE8> PID2;
	static register_unknown<0xE000EFEC> PID3;

	static register_unknown<0xE000EFF0> CID0;
	static register_unknown<0xE000EFF4> CID1;
	static register_unknown<0xE000EFF8> CID2;
	static register_unknown<0xE000EFFC> CID3;
} // namespace arm::cm7

#pragma pack(pop)
