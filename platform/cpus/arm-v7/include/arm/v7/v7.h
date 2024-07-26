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

#include <inttypes.h>
#include <stddef.h>

extern volatile intptr_t __ARMV7_ACTLR;

extern volatile intptr_t __ARMV7_SYST_CSR;
extern volatile intptr_t __ARMV7_SYST_RVR;
extern volatile intptr_t __ARMV7_SYST_CVR;
extern volatile intptr_t __ARMV7_SYST_CALIB;

extern volatile intptr_t __ARMV7_CPUID;

extern volatile intptr_t __ARMV7_ICSR;
extern volatile intptr_t __ARMV7_VTOR;

extern volatile intptr_t __ARMV7_AIRCR;

extern volatile intptr_t __ARMV7_SCR;

extern volatile intptr_t __ARMV7_CCR;

extern volatile intptr_t __ARMV7_SHPR1;
extern volatile intptr_t __ARMV7_SHPR2;
extern volatile intptr_t __ARMV7_SHPR3;
extern volatile intptr_t __ARMV7_SHCSR;

extern volatile intptr_t __ARMV7_CFSR;
extern volatile intptr_t __ARMV7_HFSR;
extern volatile intptr_t __ARMV7_DFSR;
extern volatile intptr_t __ARMV7_MMFAR;
extern volatile intptr_t __ARMV7_BFAR;

extern volatile intptr_t __ARMV7_ID_PFR0;
extern volatile intptr_t __ARMV7_ID_PFR1;

extern volatile intptr_t __ARMV7_ID_DFR0;

extern volatile intptr_t __ARMV7_ID_AFR0;

extern volatile intptr_t __ARMV7_ID_MMFR0;
extern volatile intptr_t __ARMV7_ID_MMFR1;
extern volatile intptr_t __ARMV7_ID_MMFR2;
extern volatile intptr_t __ARMV7_ID_MMFR3;

extern volatile intptr_t __ARMV7_ID_ISAR0;
extern volatile intptr_t __ARMV7_ID_ISAR1;
extern volatile intptr_t __ARMV7_ID_ISAR2;
extern volatile intptr_t __ARMV7_ID_ISAR3;
extern volatile intptr_t __ARMV7_ID_ISAR4;

extern volatile intptr_t __ARMV7_CLIDR;
extern volatile intptr_t __ARMV7_CTR;
extern volatile intptr_t __ARMV7_CCSIDR;
extern volatile intptr_t __ARMV7_CSSELR;

extern volatile intptr_t __ARMV7_DHCSR;
extern volatile intptr_t __ARMV7_DCRSR;
extern volatile intptr_t __ARMV7_DCRDR;
extern volatile intptr_t __ARMV7_DEMCR;

extern volatile intptr_t __ARMV7_CAPCR;

extern volatile intptr_t __ARMV7_STIR;

extern volatile intptr_t __ARMV7_ICIALLU;
extern volatile intptr_t __ARMV7_ICIMVAU;

extern volatile intptr_t __ARMV7_DCIMVAC;
extern volatile intptr_t __ARMV7_DCISW;
extern volatile intptr_t __ARMV7_DCCMVAU;
extern volatile intptr_t __ARMV7_DCCMVAC;
extern volatile intptr_t __ARMV7_DCCSW;
extern volatile intptr_t __ARMV7_DCCIMVAC;
extern volatile intptr_t __ARMV7_DCCISW;

extern volatile intptr_t __ARMV7_BPIALL;

extern volatile intptr_t __ARMV7_ITCMMCR;
extern volatile intptr_t __ARMV7_DTCMMCR;
extern volatile intptr_t __ARMV7_AHBPCR;
extern volatile intptr_t __ARMV7_CACR;
extern volatile intptr_t __ARMV7_AHBSCR;
extern volatile intptr_t __ARMV7_ABFSR;

extern volatile intptr_t __ARMV7_IEBR0;
extern volatile intptr_t __ARMV7_IEBR1;

extern volatile intptr_t __ARMV7_DEBR0;
extern volatile intptr_t __ARMV7_DEBR1;

extern volatile intptr_t __ARMV7_PID4;
extern volatile intptr_t __ARMV7_PID5;
extern volatile intptr_t __ARMV7_PID6;
extern volatile intptr_t __ARMV7_PID7;
extern volatile intptr_t __ARMV7_PID0;
extern volatile intptr_t __ARMV7_PID1;
extern volatile intptr_t __ARMV7_PID2;
extern volatile intptr_t __ARMV7_PID3;

extern volatile intptr_t __ARMV7_CID0;
extern volatile intptr_t __ARMV7_CID1;
extern volatile intptr_t __ARMV7_CID2;
extern volatile intptr_t __ARMV7_CID3;
