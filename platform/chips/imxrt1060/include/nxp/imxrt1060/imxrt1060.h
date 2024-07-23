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

extern volatile intptr_t __IMXRT1060_GPIO1;
extern volatile intptr_t __IMXRT1060_GPIO2;
extern volatile intptr_t __IMXRT1060_GPIO3;
extern volatile intptr_t __IMXRT1060_GPIO4;
extern volatile intptr_t __IMXRT1060_GPIO5;
extern volatile intptr_t __IMXRT1060_GPIO6;
extern volatile intptr_t __IMXRT1060_GPIO7;
extern volatile intptr_t __IMXRT1060_GPIO8;
extern volatile intptr_t __IMXRT1060_GPIO9;

extern volatile intptr_t __IMXRT1060_IOMUXC_GPR0;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR1;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR2;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR3;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR4;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR5;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR6;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR7;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR8;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR9;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR10;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR11;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR12;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR13;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR14;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR15;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR16;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR17;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR18;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR19;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR20;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR21;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR22;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR23;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR24;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR25;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR26;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR27;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR28;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR29;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR30;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR31;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR32;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR33;
extern volatile intptr_t __IMXRT1060_IOMUXC_GPR34;
