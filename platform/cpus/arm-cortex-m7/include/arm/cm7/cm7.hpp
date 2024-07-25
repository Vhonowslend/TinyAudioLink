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
#include "register.hpp"

namespace arm::cm7 {
	static register_read_write<0xE000E008> ACTLR;

	static register_unknown<0xE000E00C> __reserved0;

	static register_read_write<0xE000E010> SYST_CSR;
	static register_read_write<0xE000E014> SYST_RVR;
	static register_read_write<0xE000E018> SYST_CVR;
	static register_read<0xE000E01C>       SYST_CALIB;

	struct [[gnu::packed, gnu::aligned(1)]] iser_t {
		bool status[32];
	};

	static register_read_write<0xE000E100> NVIC_ISER0;
	static register_read_write<0xE000E104> NVIC_ISER1;
	static register_read_write<0xE000E108> NVIC_ISER2;
	static register_read_write<0xE000E10C> NVIC_ISER3;
	static register_read_write<0xE000E110> NVIC_ISER4;
	static register_read_write<0xE000E114> NVIC_ISER5;
	static register_read_write<0xE000E118> NVIC_ISER6;
	static register_read_write<0xE000E11C> NVIC_ISER7;
	static register_read_write<0xE000E120> NVIC_ISER8;
	static register_read_write<0xE000E124> NVIC_ISER9;
	static register_read_write<0xE000E128> NVIC_ISER10;
	static register_read_write<0xE000E12C> NVIC_ISER11;
	static register_read_write<0xE000E130> NVIC_ISER12;
	static register_read_write<0xE000E134> NVIC_ISER13;
	static register_read_write<0xE000E138> NVIC_ISER14;
	static register_read_write<0xE000E13C> NVIC_ISER15;

	struct [[gnu::packed, gnu::aligned(1)]] icer_t {
		bool status[32];
	};

	static register_read_write<0xE000E180> NVIC_ICER0;
	static register_read_write<0xE000E184> NVIC_ICER1;
	static register_read_write<0xE000E188> NVIC_ICER2;
	static register_read_write<0xE000E18C> NVIC_ICER3;
	static register_read_write<0xE000E190> NVIC_ICER4;
	static register_read_write<0xE000E194> NVIC_ICER5;
	static register_read_write<0xE000E198> NVIC_ICER6;
	static register_read_write<0xE000E19C> NVIC_ICER7;
	static register_read_write<0xE000E1A0> NVIC_ICER8;
	static register_read_write<0xE000E1A4> NVIC_ICER9;
	static register_read_write<0xE000E1A8> NVIC_ICER10;
	static register_read_write<0xE000E1AC> NVIC_ICER11;
	static register_read_write<0xE000E1B0> NVIC_ICER12;
	static register_read_write<0xE000E1B4> NVIC_ICER13;
	static register_read_write<0xE000E1B8> NVIC_ICER14;
	static register_read_write<0xE000E1BC> NVIC_ICER15;

	struct [[gnu::packed, gnu::aligned(1)]] ispr_t {
		bool status[32];
	};

	static register_read_write<0xE000E200> NVIC_ISPR0;
	static register_read_write<0xE000E204> NVIC_ISPR1;
	static register_read_write<0xE000E208> NVIC_ISPR2;
	static register_read_write<0xE000E20C> NVIC_ISPR3;
	static register_read_write<0xE000E210> NVIC_ISPR4;
	static register_read_write<0xE000E214> NVIC_ISPR5;
	static register_read_write<0xE000E218> NVIC_ISPR6;
	static register_read_write<0xE000E21C> NVIC_ISPR7;
	static register_read_write<0xE000E220> NVIC_ISPR8;
	static register_read_write<0xE000E224> NVIC_ISPR9;
	static register_read_write<0xE000E228> NVIC_ISPR10;
	static register_read_write<0xE000E22C> NVIC_ISPR11;
	static register_read_write<0xE000E230> NVIC_ISPR12;
	static register_read_write<0xE000E234> NVIC_ISPR13;
	static register_read_write<0xE000E238> NVIC_ISPR14;
	static register_read_write<0xE000E23C> NVIC_ISPR15;

	struct [[gnu::packed, gnu::aligned(1)]] icpr_t {
		bool status[32];
	};

	static register_read_write<0xE000E280> NVIC_ICPR0;
	static register_read_write<0xE000E284> NVIC_ICPR1;
	static register_read_write<0xE000E288> NVIC_ICPR2;
	static register_read_write<0xE000E28C> NVIC_ICPR3;
	static register_read_write<0xE000E290> NVIC_ICPR4;
	static register_read_write<0xE000E294> NVIC_ICPR5;
	static register_read_write<0xE000E298> NVIC_ICPR6;
	static register_read_write<0xE000E29C> NVIC_ICPR7;
	static register_read_write<0xE000E2A0> NVIC_ICPR8;
	static register_read_write<0xE000E2A4> NVIC_ICPR9;
	static register_read_write<0xE000E2A8> NVIC_ICPR10;
	static register_read_write<0xE000E2AC> NVIC_ICPR11;
	static register_read_write<0xE000E2B0> NVIC_ICPR12;
	static register_read_write<0xE000E2B4> NVIC_ICPR13;
	static register_read_write<0xE000E2B8> NVIC_ICPR14;
	static register_read_write<0xE000E2BC> NVIC_ICPR15;

	struct [[gnu::packed, gnu::aligned(1)]] iabr_t {
		bool status[32];
	};

	static register_read<0xE000E300> NVIC_IABR0;
	static register_read<0xE000E304> NVIC_IABR1;
	static register_read<0xE000E308> NVIC_IABR2;
	static register_read<0xE000E30C> NVIC_IABR3;
	static register_read<0xE000E310> NVIC_IABR4;
	static register_read<0xE000E314> NVIC_IABR5;
	static register_read<0xE000E318> NVIC_IABR6;
	static register_read<0xE000E31C> NVIC_IABR7;
	static register_read<0xE000E320> NVIC_IABR8;
	static register_read<0xE000E324> NVIC_IABR9;
	static register_read<0xE000E328> NVIC_IABR10;
	static register_read<0xE000E32C> NVIC_IABR11;
	static register_read<0xE000E330> NVIC_IABR12;
	static register_read<0xE000E334> NVIC_IABR13;
	static register_read<0xE000E338> NVIC_IABR14;
	static register_read<0xE000E33C> NVIC_IABR15;

	struct [[gnu::packed, gnu::aligned(1)]] ipr_t {
		uint8_t priority[4];
	};

	static register_read_write<0xE000E400> NVIC_IPR0;
	static register_read_write<0xE000E404> NVIC_IPR1;
	static register_read_write<0xE000E408> NVIC_IPR2;
	static register_read_write<0xE000E40C> NVIC_IPR3;
	static register_read_write<0xE000E410> NVIC_IPR4;
	static register_read_write<0xE000E414> NVIC_IPR5;
	static register_read_write<0xE000E418> NVIC_IPR6;
	static register_read_write<0xE000E41C> NVIC_IPR7;
	static register_read_write<0xE000E420> NVIC_IPR8;
	static register_read_write<0xE000E424> NVIC_IPR9;
	static register_read_write<0xE000E428> NVIC_IPR10;
	static register_read_write<0xE000E42C> NVIC_IPR11;
	static register_read_write<0xE000E430> NVIC_IPR12;
	static register_read_write<0xE000E434> NVIC_IPR13;
	static register_read_write<0xE000E438> NVIC_IPR14;
	static register_read_write<0xE000E43C> NVIC_IPR15;
	static register_read_write<0xE000E440> NVIC_IPR16;
	static register_read_write<0xE000E444> NVIC_IPR17;
	static register_read_write<0xE000E448> NVIC_IPR18;
	static register_read_write<0xE000E44C> NVIC_IPR19;
	static register_read_write<0xE000E450> NVIC_IPR20;
	static register_read_write<0xE000E454> NVIC_IPR21;
	static register_read_write<0xE000E458> NVIC_IPR22;
	static register_read_write<0xE000E45C> NVIC_IPR23;
	static register_read_write<0xE000E460> NVIC_IPR24;
	static register_read_write<0xE000E464> NVIC_IPR25;
	static register_read_write<0xE000E468> NVIC_IPR26;
	static register_read_write<0xE000E46C> NVIC_IPR27;
	static register_read_write<0xE000E470> NVIC_IPR28;
	static register_read_write<0xE000E474> NVIC_IPR29;
	static register_read_write<0xE000E478> NVIC_IPR30;
	static register_read_write<0xE000E47C> NVIC_IPR31;
	static register_read_write<0xE000E480> NVIC_IPR32;
	static register_read_write<0xE000E484> NVIC_IPR33;
	static register_read_write<0xE000E488> NVIC_IPR34;
	static register_read_write<0xE000E48C> NVIC_IPR35;
	static register_read_write<0xE000E490> NVIC_IPR36;
	static register_read_write<0xE000E494> NVIC_IPR37;
	static register_read_write<0xE000E498> NVIC_IPR38;
	static register_read_write<0xE000E49C> NVIC_IPR39;
	static register_read_write<0xE000E4A0> NVIC_IPR40;
	static register_read_write<0xE000E4A4> NVIC_IPR41;
	static register_read_write<0xE000E4A8> NVIC_IPR42;
	static register_read_write<0xE000E4AC> NVIC_IPR43;
	static register_read_write<0xE000E4B0> NVIC_IPR44;
	static register_read_write<0xE000E4B4> NVIC_IPR45;
	static register_read_write<0xE000E4B8> NVIC_IPR46;
	static register_read_write<0xE000E4BC> NVIC_IPR47;
	static register_read_write<0xE000E4C0> NVIC_IPR48;
	static register_read_write<0xE000E4C4> NVIC_IPR49;
	static register_read_write<0xE000E4C8> NVIC_IPR50;
	static register_read_write<0xE000E4CC> NVIC_IPR51;
	static register_read_write<0xE000E4D0> NVIC_IPR52;
	static register_read_write<0xE000E4D4> NVIC_IPR53;
	static register_read_write<0xE000E4D8> NVIC_IPR54;
	static register_read_write<0xE000E4DC> NVIC_IPR55;
	static register_read_write<0xE000E4E0> NVIC_IPR56;
	static register_read_write<0xE000E4E4> NVIC_IPR57;
	static register_read_write<0xE000E4E8> NVIC_IPR58;
	static register_read_write<0xE000E4EC> NVIC_IPR59;
	static register_read_write<0xE000E4F0> NVIC_IPR60;
	static register_read_write<0xE000E4F4> NVIC_IPR61;
	static register_read_write<0xE000E4F8> NVIC_IPR62;
	static register_read_write<0xE000E4FC> NVIC_IPR63;
	static register_read_write<0xE000E500> NVIC_IPR64;
	static register_read_write<0xE000E504> NVIC_IPR65;
	static register_read_write<0xE000E508> NVIC_IPR66;
	static register_read_write<0xE000E50C> NVIC_IPR67;
	static register_read_write<0xE000E510> NVIC_IPR68;
	static register_read_write<0xE000E514> NVIC_IPR69;
	static register_read_write<0xE000E518> NVIC_IPR70;
	static register_read_write<0xE000E51C> NVIC_IPR71;
	static register_read_write<0xE000E520> NVIC_IPR72;
	static register_read_write<0xE000E524> NVIC_IPR73;
	static register_read_write<0xE000E528> NVIC_IPR74;
	static register_read_write<0xE000E52C> NVIC_IPR75;
	static register_read_write<0xE000E530> NVIC_IPR76;
	static register_read_write<0xE000E534> NVIC_IPR77;
	static register_read_write<0xE000E538> NVIC_IPR78;
	static register_read_write<0xE000E53C> NVIC_IPR79;
	static register_read_write<0xE000E540> NVIC_IPR80;
	static register_read_write<0xE000E544> NVIC_IPR81;
	static register_read_write<0xE000E548> NVIC_IPR82;
	static register_read_write<0xE000E54C> NVIC_IPR83;
	static register_read_write<0xE000E550> NVIC_IPR84;
	static register_read_write<0xE000E554> NVIC_IPR85;
	static register_read_write<0xE000E558> NVIC_IPR86;
	static register_read_write<0xE000E55C> NVIC_IPR87;
	static register_read_write<0xE000E560> NVIC_IPR88;
	static register_read_write<0xE000E564> NVIC_IPR89;
	static register_read_write<0xE000E568> NVIC_IPR90;
	static register_read_write<0xE000E56C> NVIC_IPR91;
	static register_read_write<0xE000E570> NVIC_IPR92;
	static register_read_write<0xE000E574> NVIC_IPR93;
	static register_read_write<0xE000E578> NVIC_IPR94;
	static register_read_write<0xE000E57C> NVIC_IPR95;
	static register_read_write<0xE000E580> NVIC_IPR96;
	static register_read_write<0xE000E584> NVIC_IPR97;
	static register_read_write<0xE000E588> NVIC_IPR98;
	static register_read_write<0xE000E58C> NVIC_IPR99;
	static register_read_write<0xE000E590> NVIC_IPR100;
	static register_read_write<0xE000E594> NVIC_IPR101;
	static register_read_write<0xE000E598> NVIC_IPR102;
	static register_read_write<0xE000E59C> NVIC_IPR103;
	static register_read_write<0xE000E5A0> NVIC_IPR104;
	static register_read_write<0xE000E5A4> NVIC_IPR105;
	static register_read_write<0xE000E5A8> NVIC_IPR106;
	static register_read_write<0xE000E5AC> NVIC_IPR107;
	static register_read_write<0xE000E5B0> NVIC_IPR108;
	static register_read_write<0xE000E5B4> NVIC_IPR109;
	static register_read_write<0xE000E5B8> NVIC_IPR110;
	static register_read_write<0xE000E5BC> NVIC_IPR111;
	static register_read_write<0xE000E5C0> NVIC_IPR112;
	static register_read_write<0xE000E5C4> NVIC_IPR113;
	static register_read_write<0xE000E5C8> NVIC_IPR114;
	static register_read_write<0xE000E5CC> NVIC_IPR115;
	static register_read_write<0xE000E5D0> NVIC_IPR116;
	static register_read_write<0xE000E5D4> NVIC_IPR117;
	static register_read_write<0xE000E5D8> NVIC_IPR118;
	static register_read_write<0xE000E5DC> NVIC_IPR119;
	static register_read_write<0xE000E5E0> NVIC_IPR120;
	static register_read_write<0xE000E5E4> NVIC_IPR121;
	static register_read_write<0xE000E5E8> NVIC_IPR122;
	static register_read_write<0xE000E5EC> NVIC_IPR123;

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
	 * - [1] Write 1 to clear all configuration for exceptions, including ISPR. Should not be written to outside of
	 * debug mode.
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

	/** Debug Registers (Implementation Defined)
	 */
	static register_read_write<0xE000EDF0> DHCSR;
	static register_write<0xE000EDF4>      DCRSR;
	static register_read_write<0xE000EDF8> DCRDR;
	static register_read_write<0xE000EDFC> DEMCR;
	// 0xE000EE00 - 0xE000EEFF is reserved

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
