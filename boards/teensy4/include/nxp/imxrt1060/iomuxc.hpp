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

namespace nxp::imxrt1060::iomuxc {
	namespace gpr {
		static register_read_write<0x400AC000> GPR0;
		static register_read_write<0x400AC004> GPR1;
		static register_read_write<0x400AC008> GPR2;
		static register_read_write<0x400AC00C> GPR3;
		static register_read_write<0x400AC010> GPR4;
		static register_read_write<0x400AC014> GPR5;
		static register_read_write<0x400AC018> GPR6;
		static register_read_write<0x400AC01C> GPR7;
		static register_read_write<0x400AC020> GPR8;
		static register_read_write<0x400AC024> GPR9;
		static register_read_write<0x400AC028> GPR10;
		static register_read_write<0x400AC02C> GPR11;
		static register_read_write<0x400AC030> GPR12;
		static register_read_write<0x400AC034> GPR13;
		static register_read_write<0x400AC038> GPR14;
		static register_read_write<0x400AC03C> GPR15;
		static register_read_write<0x400AC040> GPR16;
		static register_read_write<0x400AC044> GPR17;
		static register_read_write<0x400AC048> GPR18;
		static register_read_write<0x400AC04C> GPR19;
		static register_read_write<0x400AC050> GPR20;
		static register_read_write<0x400AC054> GPR21;
		static register_read_write<0x400AC058> GPR22;
		static register_read_write<0x400AC05C> GPR23;
		static register_read_write<0x400AC060> GPR24;
		static register_read_write<0x400AC064> GPR25;
		static register_read_write<0x400AC068> GPR26;
		static register_read_write<0x400AC06C> GPR27;
		static register_read_write<0x400AC070> GPR28;
		static register_read_write<0x400AC074> GPR29;
		static register_read_write<0x400AC078> GPR30;
		static register_read_write<0x400AC07C> GPR31;
		static register_read_write<0x400AC080> GPR32;
		static register_read_write<0x400AC084> GPR33;
		static register_read_write<0x400AC088> GPR34;
	} // namespace gpr

	namespace snvs {
		static register_read_write<0x400A8000> SW_MUX_CTL_PAD_WAKEUP;
		static register_read_write<0x400A8004> SW_MUX_CTL_PAD_PMIC_ON_REQ;
		static register_read_write<0x400A8008> SW_MUX_CTL_PAD_PMIC_STBY_REQ;
		static register_read_write<0x400A800C> SW_PAD_CTL_PAD_TEST_MODE;
		static register_read_write<0x400A8010> SW_PAD_CTL_PAD_POR_B;
		static register_read_write<0x400A8014> SW_PAD_CTL_PAD_ONOFF;
		static register_read_write<0x400A8018> SW_PAD_CTL_PAD_WAKEUP;
		static register_read_write<0x400A801C> SW_PAD_CTL_PAD_PMIC_ON_REQ;
		static register_read_write<0x400A8020> SW_PAD_CTL_PAD_PMIC_STBY_REQ;

		namespace gpr {
			static register_read_write<0x400A4000> GPR0;
			static register_read_write<0x400A4004> GPR1;
			static register_read_write<0x400A4008> GPR2;
			static register_read_write<0x400A400C> GPR3;
		} // namespace gpr
	} // namespace snvs

	static register_read_write<0x401F8014> SW_MUX_CTL_PAD_GPIO_EMC_00;
	static register_read_write<0x401F8018> SW_MUX_CTL_PAD_GPIO_EMC_01;
	static register_read_write<0x401F801C> SW_MUX_CTL_PAD_GPIO_EMC_02;
	static register_read_write<0x401F8020> SW_MUX_CTL_PAD_GPIO_EMC_03;
	static register_read_write<0x401F8024> SW_MUX_CTL_PAD_GPIO_EMC_04;
	static register_read_write<0x401F8028> SW_MUX_CTL_PAD_GPIO_EMC_05;
	static register_read_write<0x401F802C> SW_MUX_CTL_PAD_GPIO_EMC_06;
	static register_read_write<0x401F8030> SW_MUX_CTL_PAD_GPIO_EMC_07;
	static register_read_write<0x401F8034> SW_MUX_CTL_PAD_GPIO_EMC_08;
	static register_read_write<0x401F8038> SW_MUX_CTL_PAD_GPIO_EMC_09;
	static register_read_write<0x401F803C> SW_MUX_CTL_PAD_GPIO_EMC_10;
	static register_read_write<0x401F8040> SW_MUX_CTL_PAD_GPIO_EMC_11;
	static register_read_write<0x401F8044> SW_MUX_CTL_PAD_GPIO_EMC_12;
	static register_read_write<0x401F8048> SW_MUX_CTL_PAD_GPIO_EMC_13;
	static register_read_write<0x401F804C> SW_MUX_CTL_PAD_GPIO_EMC_14;
	static register_read_write<0x401F8050> SW_MUX_CTL_PAD_GPIO_EMC_15;
	static register_read_write<0x401F8054> SW_MUX_CTL_PAD_GPIO_EMC_16;
	static register_read_write<0x401F8058> SW_MUX_CTL_PAD_GPIO_EMC_17;
	static register_read_write<0x401F805C> SW_MUX_CTL_PAD_GPIO_EMC_18;
	static register_read_write<0x401F8060> SW_MUX_CTL_PAD_GPIO_EMC_19;
	static register_read_write<0x401F8064> SW_MUX_CTL_PAD_GPIO_EMC_20;
	static register_read_write<0x401F8068> SW_MUX_CTL_PAD_GPIO_EMC_21;
	static register_read_write<0x401F806C> SW_MUX_CTL_PAD_GPIO_EMC_22;
	static register_read_write<0x401F8070> SW_MUX_CTL_PAD_GPIO_EMC_23;
	static register_read_write<0x401F8074> SW_MUX_CTL_PAD_GPIO_EMC_24;
	static register_read_write<0x401F8078> SW_MUX_CTL_PAD_GPIO_EMC_25;
	static register_read_write<0x401F807C> SW_MUX_CTL_PAD_GPIO_EMC_26;
	static register_read_write<0x401F8080> SW_MUX_CTL_PAD_GPIO_EMC_27;
	static register_read_write<0x401F8084> SW_MUX_CTL_PAD_GPIO_EMC_28;
	static register_read_write<0x401F8088> SW_MUX_CTL_PAD_GPIO_EMC_29;
	static register_read_write<0x401F808C> SW_MUX_CTL_PAD_GPIO_EMC_30;
	static register_read_write<0x401F8090> SW_MUX_CTL_PAD_GPIO_EMC_31;
	static register_read_write<0x401F8094> SW_MUX_CTL_PAD_GPIO_EMC_32;
	static register_read_write<0x401F8098> SW_MUX_CTL_PAD_GPIO_EMC_33;
	static register_read_write<0x401F809C> SW_MUX_CTL_PAD_GPIO_EMC_34;
	static register_read_write<0x401F80A0> SW_MUX_CTL_PAD_GPIO_EMC_35;
	static register_read_write<0x401F80A4> SW_MUX_CTL_PAD_GPIO_EMC_36;
	static register_read_write<0x401F80A8> SW_MUX_CTL_PAD_GPIO_EMC_37;
	static register_read_write<0x401F80AC> SW_MUX_CTL_PAD_GPIO_EMC_38;
	static register_read_write<0x401F80B0> SW_MUX_CTL_PAD_GPIO_EMC_39;
	static register_read_write<0x401F80B4> SW_MUX_CTL_PAD_GPIO_EMC_40;
	static register_read_write<0x401F80B8> SW_MUX_CTL_PAD_GPIO_EMC_41;

	static register_read_write<0x401F80BC> SW_MUX_CTL_PAD_GPIO_AD_B0_00;
	static register_read_write<0x401F80C0> SW_MUX_CTL_PAD_GPIO_AD_B0_01;
	static register_read_write<0x401F80C4> SW_MUX_CTL_PAD_GPIO_AD_B0_02;
	static register_read_write<0x401F80C8> SW_MUX_CTL_PAD_GPIO_AD_B0_03;
	static register_read_write<0x401F80CC> SW_MUX_CTL_PAD_GPIO_AD_B0_04;
	static register_read_write<0x401F80D0> SW_MUX_CTL_PAD_GPIO_AD_B0_05;
	static register_read_write<0x401F80D4> SW_MUX_CTL_PAD_GPIO_AD_B0_06;
	static register_read_write<0x401F80D8> SW_MUX_CTL_PAD_GPIO_AD_B0_07;
	static register_read_write<0x401F80DC> SW_MUX_CTL_PAD_GPIO_AD_B0_08;
	static register_read_write<0x401F80E0> SW_MUX_CTL_PAD_GPIO_AD_B0_09;
	static register_read_write<0x401F80E4> SW_MUX_CTL_PAD_GPIO_AD_B0_10;
	static register_read_write<0x401F80E8> SW_MUX_CTL_PAD_GPIO_AD_B0_11;
	static register_read_write<0x401F80EC> SW_MUX_CTL_PAD_GPIO_AD_B0_12;
	static register_read_write<0x401F80F0> SW_MUX_CTL_PAD_GPIO_AD_B0_13;
	static register_read_write<0x401F80F4> SW_MUX_CTL_PAD_GPIO_AD_B0_14;
	static register_read_write<0x401F80F8> SW_MUX_CTL_PAD_GPIO_AD_B0_15;

	static register_read_write<0x401F80FC> SW_MUX_CTL_PAD_GPIO_AD_B1_00;
	static register_read_write<0x401F8100> SW_MUX_CTL_PAD_GPIO_AD_B1_01;
	static register_read_write<0x401F8104> SW_MUX_CTL_PAD_GPIO_AD_B1_02;
	static register_read_write<0x401F8108> SW_MUX_CTL_PAD_GPIO_AD_B1_03;
	static register_read_write<0x401F810C> SW_MUX_CTL_PAD_GPIO_AD_B1_04;
	static register_read_write<0x401F8110> SW_MUX_CTL_PAD_GPIO_AD_B1_05;
	static register_read_write<0x401F8114> SW_MUX_CTL_PAD_GPIO_AD_B1_06;
	static register_read_write<0x401F8118> SW_MUX_CTL_PAD_GPIO_AD_B1_07;
	static register_read_write<0x401F811C> SW_MUX_CTL_PAD_GPIO_AD_B1_08;
	static register_read_write<0x401F8120> SW_MUX_CTL_PAD_GPIO_AD_B1_09;
	static register_read_write<0x401F8124> SW_MUX_CTL_PAD_GPIO_AD_B1_10;
	static register_read_write<0x401F8128> SW_MUX_CTL_PAD_GPIO_AD_B1_11;
	static register_read_write<0x401F812C> SW_MUX_CTL_PAD_GPIO_AD_B1_12;
	static register_read_write<0x401F8130> SW_MUX_CTL_PAD_GPIO_AD_B1_13;
	static register_read_write<0x401F8134> SW_MUX_CTL_PAD_GPIO_AD_B1_14;
	static register_read_write<0x401F8138> SW_MUX_CTL_PAD_GPIO_AD_B1_15;

	static register_read_write<0x401F813C> SW_MUX_CTL_PAD_GPIO_B0_00;
	static register_read_write<0x401F8140> SW_MUX_CTL_PAD_GPIO_B0_01;
	static register_read_write<0x401F8144> SW_MUX_CTL_PAD_GPIO_B0_02;
	static register_read_write<0x401F8148> SW_MUX_CTL_PAD_GPIO_B0_03;
	static register_read_write<0x401F814C> SW_MUX_CTL_PAD_GPIO_B0_04;
	static register_read_write<0x401F8150> SW_MUX_CTL_PAD_GPIO_B0_05;
	static register_read_write<0x401F8154> SW_MUX_CTL_PAD_GPIO_B0_06;
	static register_read_write<0x401F8158> SW_MUX_CTL_PAD_GPIO_B0_07;
	static register_read_write<0x401F815C> SW_MUX_CTL_PAD_GPIO_B0_08;
	static register_read_write<0x401F8160> SW_MUX_CTL_PAD_GPIO_B0_09;
	static register_read_write<0x401F8164> SW_MUX_CTL_PAD_GPIO_B0_10;
	static register_read_write<0x401F8168> SW_MUX_CTL_PAD_GPIO_B0_11;
	static register_read_write<0x401F816C> SW_MUX_CTL_PAD_GPIO_B0_12;
	static register_read_write<0x401F8170> SW_MUX_CTL_PAD_GPIO_B0_13;
	static register_read_write<0x401F8174> SW_MUX_CTL_PAD_GPIO_B0_14;
	static register_read_write<0x401F8178> SW_MUX_CTL_PAD_GPIO_B0_15;

	static register_read_write<0x401F817C> SW_MUX_CTL_PAD_GPIO_B1_00;
	static register_read_write<0x401F8180> SW_MUX_CTL_PAD_GPIO_B1_01;
	static register_read_write<0x401F8184> SW_MUX_CTL_PAD_GPIO_B1_02;
	static register_read_write<0x401F8188> SW_MUX_CTL_PAD_GPIO_B1_03;
	static register_read_write<0x401F818C> SW_MUX_CTL_PAD_GPIO_B1_04;
	static register_read_write<0x401F8190> SW_MUX_CTL_PAD_GPIO_B1_05;
	static register_read_write<0x401F8194> SW_MUX_CTL_PAD_GPIO_B1_06;
	static register_read_write<0x401F8198> SW_MUX_CTL_PAD_GPIO_B1_07;
	static register_read_write<0x401F819C> SW_MUX_CTL_PAD_GPIO_B1_08;
	static register_read_write<0x401F81A0> SW_MUX_CTL_PAD_GPIO_B1_09;
	static register_read_write<0x401F81A4> SW_MUX_CTL_PAD_GPIO_B1_10;
	static register_read_write<0x401F81A8> SW_MUX_CTL_PAD_GPIO_B1_11;
	static register_read_write<0x401F81AC> SW_MUX_CTL_PAD_GPIO_B1_12;
	static register_read_write<0x401F81B0> SW_MUX_CTL_PAD_GPIO_B1_13;
	static register_read_write<0x401F81B4> SW_MUX_CTL_PAD_GPIO_B1_14;
	static register_read_write<0x401F81B8> SW_MUX_CTL_PAD_GPIO_B1_15;

	static register_read_write<0x401F81BC> SW_MUX_CTL_PAD_GPIO_SD_B0_00;
	static register_read_write<0x401F81C0> SW_MUX_CTL_PAD_GPIO_SD_B0_01;
	static register_read_write<0x401F81C4> SW_MUX_CTL_PAD_GPIO_SD_B0_02;
	static register_read_write<0x401F81C8> SW_MUX_CTL_PAD_GPIO_SD_B0_03;
	static register_read_write<0x401F81CC> SW_MUX_CTL_PAD_GPIO_SD_B0_04;
	static register_read_write<0x401F81D0> SW_MUX_CTL_PAD_GPIO_SD_B0_05;

	static register_read_write<0x401F81D4> SW_MUX_CTL_PAD_GPIO_SD_B1_00;
	static register_read_write<0x401F81D8> SW_MUX_CTL_PAD_GPIO_SD_B1_01;
	static register_read_write<0x401F81DC> SW_MUX_CTL_PAD_GPIO_SD_B1_02;
	static register_read_write<0x401F81E0> SW_MUX_CTL_PAD_GPIO_SD_B1_03;
	static register_read_write<0x401F81E4> SW_MUX_CTL_PAD_GPIO_SD_B1_04;
	static register_read_write<0x401F81E8> SW_MUX_CTL_PAD_GPIO_SD_B1_05;
	static register_read_write<0x401F81EC> SW_MUX_CTL_PAD_GPIO_SD_B1_06;
	static register_read_write<0x401F81F0> SW_MUX_CTL_PAD_GPIO_SD_B1_07;
	static register_read_write<0x401F81F4> SW_MUX_CTL_PAD_GPIO_SD_B1_08;
	static register_read_write<0x401F81F8> SW_MUX_CTL_PAD_GPIO_SD_B1_09;
	static register_read_write<0x401F81FC> SW_MUX_CTL_PAD_GPIO_SD_B1_10;
	static register_read_write<0x401F8200> SW_MUX_CTL_PAD_GPIO_SD_B1_11;

	static register_read_write<0x401F8204> SW_PAD_CTL_PAD_GPIO_EMC_00;
	static register_read_write<0x401F8208> SW_PAD_CTL_PAD_GPIO_EMC_01;
	static register_read_write<0x401F820C> SW_PAD_CTL_PAD_GPIO_EMC_02;
	static register_read_write<0x401F8210> SW_PAD_CTL_PAD_GPIO_EMC_03;
	static register_read_write<0x401F8214> SW_PAD_CTL_PAD_GPIO_EMC_04;
	static register_read_write<0x401F8218> SW_PAD_CTL_PAD_GPIO_EMC_05;
	static register_read_write<0x401F821C> SW_PAD_CTL_PAD_GPIO_EMC_06;
	static register_read_write<0x401F8220> SW_PAD_CTL_PAD_GPIO_EMC_07;
	static register_read_write<0x401F8224> SW_PAD_CTL_PAD_GPIO_EMC_08;
	static register_read_write<0x401F8228> SW_PAD_CTL_PAD_GPIO_EMC_09;
	static register_read_write<0x401F822C> SW_PAD_CTL_PAD_GPIO_EMC_10;
	static register_read_write<0x401F8230> SW_PAD_CTL_PAD_GPIO_EMC_11;
	static register_read_write<0x401F8234> SW_PAD_CTL_PAD_GPIO_EMC_12;
	static register_read_write<0x401F8238> SW_PAD_CTL_PAD_GPIO_EMC_13;
	static register_read_write<0x401F823C> SW_PAD_CTL_PAD_GPIO_EMC_14;
	static register_read_write<0x401F8240> SW_PAD_CTL_PAD_GPIO_EMC_15;
	static register_read_write<0x401F8244> SW_PAD_CTL_PAD_GPIO_EMC_16;
	static register_read_write<0x401F8248> SW_PAD_CTL_PAD_GPIO_EMC_17;
	static register_read_write<0x401F824C> SW_PAD_CTL_PAD_GPIO_EMC_18;
	static register_read_write<0x401F8250> SW_PAD_CTL_PAD_GPIO_EMC_19;
	static register_read_write<0x401F8254> SW_PAD_CTL_PAD_GPIO_EMC_20;
	static register_read_write<0x401F8258> SW_PAD_CTL_PAD_GPIO_EMC_21;
	static register_read_write<0x401F825C> SW_PAD_CTL_PAD_GPIO_EMC_22;
	static register_read_write<0x401F8260> SW_PAD_CTL_PAD_GPIO_EMC_23;
	static register_read_write<0x401F8264> SW_PAD_CTL_PAD_GPIO_EMC_24;
	static register_read_write<0x401F8268> SW_PAD_CTL_PAD_GPIO_EMC_25;
	static register_read_write<0x401F826C> SW_PAD_CTL_PAD_GPIO_EMC_26;
	static register_read_write<0x401F8270> SW_PAD_CTL_PAD_GPIO_EMC_27;
	static register_read_write<0x401F8274> SW_PAD_CTL_PAD_GPIO_EMC_28;
	static register_read_write<0x401F8278> SW_PAD_CTL_PAD_GPIO_EMC_29;
	static register_read_write<0x401F827C> SW_PAD_CTL_PAD_GPIO_EMC_30;
	static register_read_write<0x401F8280> SW_PAD_CTL_PAD_GPIO_EMC_31;
	static register_read_write<0x401F8284> SW_PAD_CTL_PAD_GPIO_EMC_32;
	static register_read_write<0x401F8288> SW_PAD_CTL_PAD_GPIO_EMC_33;
	static register_read_write<0x401F828C> SW_PAD_CTL_PAD_GPIO_EMC_34;
	static register_read_write<0x401F8290> SW_PAD_CTL_PAD_GPIO_EMC_35;
	static register_read_write<0x401F8294> SW_PAD_CTL_PAD_GPIO_EMC_36;
	static register_read_write<0x401F8298> SW_PAD_CTL_PAD_GPIO_EMC_37;
	static register_read_write<0x401F829C> SW_PAD_CTL_PAD_GPIO_EMC_38;
	static register_read_write<0x401F82A0> SW_PAD_CTL_PAD_GPIO_EMC_39;
	static register_read_write<0x401F82A4> SW_PAD_CTL_PAD_GPIO_EMC_40;
	static register_read_write<0x401F82A8> SW_PAD_CTL_PAD_GPIO_EMC_41;

	static register_read_write<0x401F82AC> SW_PAD_CTL_PAD_GPIO_AD_B0_00;
	static register_read_write<0x401F82B0> SW_PAD_CTL_PAD_GPIO_AD_B0_01;
	static register_read_write<0x401F82B4> SW_PAD_CTL_PAD_GPIO_AD_B0_02;
	static register_read_write<0x401F82B8> SW_PAD_CTL_PAD_GPIO_AD_B0_03;
	static register_read_write<0x401F82BC> SW_PAD_CTL_PAD_GPIO_AD_B0_04;
	static register_read_write<0x401F82C0> SW_PAD_CTL_PAD_GPIO_AD_B0_05;
	static register_read_write<0x401F82C4> SW_PAD_CTL_PAD_GPIO_AD_B0_06;
	static register_read_write<0x401F82C8> SW_PAD_CTL_PAD_GPIO_AD_B0_07;
	static register_read_write<0x401F82CC> SW_PAD_CTL_PAD_GPIO_AD_B0_08;
	static register_read_write<0x401F82D0> SW_PAD_CTL_PAD_GPIO_AD_B0_09;
	static register_read_write<0x401F82D4> SW_PAD_CTL_PAD_GPIO_AD_B0_10;
	static register_read_write<0x401F82D8> SW_PAD_CTL_PAD_GPIO_AD_B0_11;
	static register_read_write<0x401F82DC> SW_PAD_CTL_PAD_GPIO_AD_B0_12;
	static register_read_write<0x401F82E0> SW_PAD_CTL_PAD_GPIO_AD_B0_13;
	static register_read_write<0x401F82E4> SW_PAD_CTL_PAD_GPIO_AD_B0_14;
	static register_read_write<0x401F82E8> SW_PAD_CTL_PAD_GPIO_AD_B0_15;

	static register_read_write<0x401F82EC> SW_PAD_CTL_PAD_GPIO_AD_B1_00;
	static register_read_write<0x401F82F0> SW_PAD_CTL_PAD_GPIO_AD_B1_01;
	static register_read_write<0x401F82F4> SW_PAD_CTL_PAD_GPIO_AD_B1_02;
	static register_read_write<0x401F82F8> SW_PAD_CTL_PAD_GPIO_AD_B1_03;
	static register_read_write<0x401F82FC> SW_PAD_CTL_PAD_GPIO_AD_B1_04;
	static register_read_write<0x401F8300> SW_PAD_CTL_PAD_GPIO_AD_B1_05;
	static register_read_write<0x401F8304> SW_PAD_CTL_PAD_GPIO_AD_B1_06;
	static register_read_write<0x401F8308> SW_PAD_CTL_PAD_GPIO_AD_B1_07;
	static register_read_write<0x401F830C> SW_PAD_CTL_PAD_GPIO_AD_B1_08;
	static register_read_write<0x401F8310> SW_PAD_CTL_PAD_GPIO_AD_B1_09;
	static register_read_write<0x401F8314> SW_PAD_CTL_PAD_GPIO_AD_B1_10;
	static register_read_write<0x401F8318> SW_PAD_CTL_PAD_GPIO_AD_B1_11;
	static register_read_write<0x401F831C> SW_PAD_CTL_PAD_GPIO_AD_B1_12;
	static register_read_write<0x401F8320> SW_PAD_CTL_PAD_GPIO_AD_B1_13;
	static register_read_write<0x401F8324> SW_PAD_CTL_PAD_GPIO_AD_B1_14;
	static register_read_write<0x401F8328> SW_PAD_CTL_PAD_GPIO_AD_B1_15;

	static register_read_write<0x401F832C> SW_PAD_CTL_PAD_GPIO_B0_00;
	static register_read_write<0x401F8330> SW_PAD_CTL_PAD_GPIO_B0_01;
	static register_read_write<0x401F8334> SW_PAD_CTL_PAD_GPIO_B0_02;
	static register_read_write<0x401F8338> SW_PAD_CTL_PAD_GPIO_B0_03;
	static register_read_write<0x401F833C> SW_PAD_CTL_PAD_GPIO_B0_04;
	static register_read_write<0x401F8340> SW_PAD_CTL_PAD_GPIO_B0_05;
	static register_read_write<0x401F8344> SW_PAD_CTL_PAD_GPIO_B0_06;
	static register_read_write<0x401F8348> SW_PAD_CTL_PAD_GPIO_B0_07;
	static register_read_write<0x401F834C> SW_PAD_CTL_PAD_GPIO_B0_08;
	static register_read_write<0x401F8350> SW_PAD_CTL_PAD_GPIO_B0_09;
	static register_read_write<0x401F8354> SW_PAD_CTL_PAD_GPIO_B0_10;
	static register_read_write<0x401F8358> SW_PAD_CTL_PAD_GPIO_B0_11;
	static register_read_write<0x401F835C> SW_PAD_CTL_PAD_GPIO_B0_12;
	static register_read_write<0x401F8360> SW_PAD_CTL_PAD_GPIO_B0_13;
	static register_read_write<0x401F8364> SW_PAD_CTL_PAD_GPIO_B0_14;
	static register_read_write<0x401F8368> SW_PAD_CTL_PAD_GPIO_B0_15;

	static register_read_write<0x401F836C> SW_PAD_CTL_PAD_GPIO_B1_00;
	static register_read_write<0x401F8370> SW_PAD_CTL_PAD_GPIO_B1_01;
	static register_read_write<0x401F8374> SW_PAD_CTL_PAD_GPIO_B1_02;
	static register_read_write<0x401F8378> SW_PAD_CTL_PAD_GPIO_B1_03;
	static register_read_write<0x401F837C> SW_PAD_CTL_PAD_GPIO_B1_04;
	static register_read_write<0x401F8380> SW_PAD_CTL_PAD_GPIO_B1_05;
	static register_read_write<0x401F8384> SW_PAD_CTL_PAD_GPIO_B1_06;
	static register_read_write<0x401F8388> SW_PAD_CTL_PAD_GPIO_B1_07;
	static register_read_write<0x401F838C> SW_PAD_CTL_PAD_GPIO_B1_08;
	static register_read_write<0x401F8390> SW_PAD_CTL_PAD_GPIO_B1_09;
	static register_read_write<0x401F8394> SW_PAD_CTL_PAD_GPIO_B1_10;
	static register_read_write<0x401F8398> SW_PAD_CTL_PAD_GPIO_B1_11;
	static register_read_write<0x401F839C> SW_PAD_CTL_PAD_GPIO_B1_12;
	static register_read_write<0x401F83A0> SW_PAD_CTL_PAD_GPIO_B1_13;
	static register_read_write<0x401F83A4> SW_PAD_CTL_PAD_GPIO_B1_14;
	static register_read_write<0x401F83A8> SW_PAD_CTL_PAD_GPIO_B1_15;

	static register_read_write<0x401F83AC> SW_PAD_CTL_PAD_GPIO_SD_B0_00;
	static register_read_write<0x401F83B0> SW_PAD_CTL_PAD_GPIO_SD_B0_01;
	static register_read_write<0x401F83B4> SW_PAD_CTL_PAD_GPIO_SD_B0_02;
	static register_read_write<0x401F83B8> SW_PAD_CTL_PAD_GPIO_SD_B0_03;
	static register_read_write<0x401F83BC> SW_PAD_CTL_PAD_GPIO_SD_B0_04;
	static register_read_write<0x401F83C0> SW_PAD_CTL_PAD_GPIO_SD_B0_05;

	static register_read_write<0x401F83C4> SW_PAD_CTL_PAD_GPIO_SD_B1_00;
	static register_read_write<0x401F83C8> SW_PAD_CTL_PAD_GPIO_SD_B1_01;
	static register_read_write<0x401F83CC> SW_PAD_CTL_PAD_GPIO_SD_B1_02;
	static register_read_write<0x401F83D0> SW_PAD_CTL_PAD_GPIO_SD_B1_03;
	static register_read_write<0x401F83D4> SW_PAD_CTL_PAD_GPIO_SD_B1_04;
	static register_read_write<0x401F83D8> SW_PAD_CTL_PAD_GPIO_SD_B1_05;
	static register_read_write<0x401F83DC> SW_PAD_CTL_PAD_GPIO_SD_B1_06;
	static register_read_write<0x401F83E0> SW_PAD_CTL_PAD_GPIO_SD_B1_07;
	static register_read_write<0x401F83E4> SW_PAD_CTL_PAD_GPIO_SD_B1_08;
	static register_read_write<0x401F83E8> SW_PAD_CTL_PAD_GPIO_SD_B1_09;
	static register_read_write<0x401F83EC> SW_PAD_CTL_PAD_GPIO_SD_B1_10;
	static register_read_write<0x401F83F0> SW_PAD_CTL_PAD_GPIO_SD_B1_11;

	static register_read_write<0x401F83F4> ANATOP_USB_OTG1_ID_SELECT_INPUT;
	static register_read_write<0x401F83F8> ANATOP_USB_OTG2_ID_SELECT_INPUT;
	static register_read_write<0x401F83FC> CCM_PMIC_READY_SELECT_INPUT;

	static register_read_write<0x401F8400> CSI_DATA02_SELECT_INPUT;
	static register_read_write<0x401F8404> CSI_DATA03_SELECT_INPUT;
	static register_read_write<0x401F8408> CSI_DATA04_SELECT_INPUT;
	static register_read_write<0x401F840C> CSI_DATA05_SELECT_INPUT;
	static register_read_write<0x401F8410> CSI_DATA06_SELECT_INPUT;
	static register_read_write<0x401F8414> CSI_DATA07_SELECT_INPUT;
	static register_read_write<0x401F8418> CSI_DATA08_SELECT_INPUT;
	static register_read_write<0x401F841C> CSI_DATA09_SELECT_INPUT;
	static register_read_write<0x401F8420> CSI_HSYNC_SELECT_INPUT;
	static register_read_write<0x401F8424> CSI_PIXCLK_SELECT_INPUT;
	static register_read_write<0x401F8428> CSI_VSYNC_SELECT_INPUT;

	static register_read_write<0x401F842C> ENET_IPG_CLK_RMII_SELECT_INPUT;
	static register_read_write<0x401F8430> ENET_MDIO_SELECT_INPUT;
	static register_read_write<0x401F8434> ENET0_RXDATA_SELECT_INPUT;
	static register_read_write<0x401F8438> ENET1_RXDATA_SELECT_INPUT;
	static register_read_write<0x401F843C> ENET_RXEN_SELECT_INPUT;
	static register_read_write<0x401F8440> ENET_RXERR_SELECT_INPUT;
	static register_read_write<0x401F8444> ENET0_TIMER_SELECT_INPUT;
	static register_read_write<0x401F8448> ENET_TXCLK_SELECT_INPUT;

	static register_read_write<0x401F844C> FLEXCAN1_RX_SELECT_INPUT;
	static register_read_write<0x401F8450> FLEXCAN2_RX_SELECT_INPUT;

	static register_read_write<0x401F8454> FLEXPWM1_PWMA3_SELECT_INPUT;
	static register_read_write<0x401F8458> FLEXPWM1_PWMA0_SELECT_INPUT;
	static register_read_write<0x401F845C> FLEXPWM1_PWMA1_SELECT_INPUT;
	static register_read_write<0x401F8460> FLEXPWM1_PWMA2_SELECT_INPUT;
	static register_read_write<0x401F8464> FLEXPWM1_PWMB3_SELECT_INPUT;
	static register_read_write<0x401F8468> FLEXPWM1_PWMB0_SELECT_INPUT;
	static register_read_write<0x401F846C> FLEXPWM1_PWMB1_SELECT_INPUT;
	static register_read_write<0x401F8470> FLEXPWM1_PWMB2_SELECT_INPUT;

	static register_read_write<0x401F8474> FLEXPWM2_PWMA3_SELECT_INPUT;
	static register_read_write<0x401F8478> FLEXPWM2_PWMA0_SELECT_INPUT;
	static register_read_write<0x401F847C> FLEXPWM2_PWMA1_SELECT_INPUT;
	static register_read_write<0x401F8480> FLEXPWM2_PWMA2_SELECT_INPUT;
	static register_read_write<0x401F8484> FLEXPWM2_PWMB3_SELECT_INPUT;
	static register_read_write<0x401F8488> FLEXPWM2_PWMB0_SELECT_INPUT;
	static register_read_write<0x401F848C> FLEXPWM2_PWMB1_SELECT_INPUT;
	static register_read_write<0x401F8490> FLEXPWM2_PWMB2_SELECT_INPUT;

	static register_read_write<0x401F8494> FLEXPWM4_PWMA0_SELECT_INPUT;
	static register_read_write<0x401F8498> FLEXPWM4_PWMA1_SELECT_INPUT;
	static register_read_write<0x401F849C> FLEXPWM4_PWMA2_SELECT_INPUT;
	static register_read_write<0x401F84A0> FLEXPWM4_PWMA3_SELECT_INPUT;

	static register_read_write<0x401F84A4> FLEXSPIA_DQS_SELECT_INPUT;
	static register_read_write<0x401F84A8> FLEXSPIA_DATA0_SELECT_INPUT;
	static register_read_write<0x401F84AC> FLEXSPIA_DATA1_SELECT_INPUT;
	static register_read_write<0x401F84B0> FLEXSPIA_DATA2_SELECT_INPUT;
	static register_read_write<0x401F84B4> FLEXSPIA_DATA3_SELECT_INPUT;

	static register_read_write<0x401F84B8> FLEXSPIB_DATA0_SELECT_INPUT;
	static register_read_write<0x401F84BC> FLEXSPIB_DATA1_SELECT_INPUT;
	static register_read_write<0x401F84C0> FLEXSPIB_DATA2_SELECT_INPUT;
	static register_read_write<0x401F84C4> FLEXSPIB_DATA3_SELECT_INPUT;

	static register_read_write<0x401F84C8> FLEXSPIA_SCK_SELECT_INPUT;

	static register_read_write<0x401F84CC> LPI2C1_SCL_SELECT_INPUT;
	static register_read_write<0x401F84D0> LPI2C1_SDA_SELECT_INPUT;
	static register_read_write<0x401F84D4> LPI2C2_SCL_SELECT_INPUT;
	static register_read_write<0x401F84D8> LPI2C2_SDA_SELECT_INPUT;
	static register_read_write<0x401F84DC> LPI2C3_SCL_SELECT_INPUT;
	static register_read_write<0x401F84E0> LPI2C3_SDA_SELECT_INPUT;
	static register_read_write<0x401F84E4> LPI2C4_SCL_SELECT_INPUT;
	static register_read_write<0x401F84E8> LPI2C4_SDA_SELECT_INPUT;

	static register_read_write<0x401F84EC> LPSPI1_PCS0_SELECT_INPUT;
	static register_read_write<0x401F84F0> LPSPI1_SCK_SELECT_INPUT;
	static register_read_write<0x401F84F4> LPSPI1_SDI_SELECT_INPUT;
	static register_read_write<0x401F84F8> LPSPI1_SDO_SELECT_INPUT;

	static register_read_write<0x401F84FC> LPSPI2_PCS0_SELECT_INPUT;
	static register_read_write<0x401F8500> LPSPI2_SCK_SELECT_INPUT;
	static register_read_write<0x401F8504> LPSPI2_SDI_SELECT_INPUT;
	static register_read_write<0x401F8508> LPSPI2_SDO_SELECT_INPUT;

	static register_read_write<0x401F850C> LPSPI3_PCS0_SELECT_INPUT;
	static register_read_write<0x401F8510> LPSPI3_SCK_SELECT_INPUT;
	static register_read_write<0x401F8514> LPSPI3_SDI_SELECT_INPUT;
	static register_read_write<0x401F8518> LPSPI3_SDO_SELECT_INPUT;

	static register_read_write<0x401F851C> LPSPI4_PCS0_SELECT_INPUT;
	static register_read_write<0x401F8520> LPSPI4_SCK_SELECT_INPUT;
	static register_read_write<0x401F8524> LPSPI4_SDI_SELECT_INPUT;
	static register_read_write<0x401F8528> LPSPI4_SDO_SELECT_INPUT;

	static register_read_write<0x401F852C> LPUART2_RX_SELECT_INPUT;
	static register_read_write<0x401F8530> LPUART2_TX_SELECT_INPUT;

	static register_read_write<0x401F8534> LPUART3_CTS_B_SELECT_INPUT;
	static register_read_write<0x401F8538> LPUART3_RX_SELECT_INPUT;
	static register_read_write<0x401F853C> LPUART3_TX_SELECT_INPUT;

	static register_read_write<0x401F8540> LPUART4_RX_SELECT_INPUT;
	static register_read_write<0x401F8544> LPUART4_TX_SELECT_INPUT;

	static register_read_write<0x401F8548> LPUART5_RX_SELECT_INPUT;
	static register_read_write<0x401F854C> LPUART5_TX_SELECT_INPUT;

	static register_read_write<0x401F8550> LPUART6_RX_SELECT_INPUT;
	static register_read_write<0x401F8554> LPUART6_TX_SELECT_INPUT;

	static register_read_write<0x401F8558> LPUART7_RX_SELECT_INPUT;
	static register_read_write<0x401F855C> LPUART7_TX_SELECT_INPUT;

	static register_read_write<0x401F8560> LPUART8_RX_SELECT_INPUT;
	static register_read_write<0x401F8564> LPUART8_TX_SELECT_INPUT;

	static register_read_write<0x401F8568> NMI_SELECT_INPUT;

	static register_read_write<0x401F856C> QTIMER2_TIMER0_SELECT_INPUT;
	static register_read_write<0x401F8570> QTIMER2_TIMER1_SELECT_INPUT;
	static register_read_write<0x401F8574> QTIMER2_TIMER2_SELECT_INPUT;
	static register_read_write<0x401F8578> QTIMER2_TIMER3_SELECT_INPUT;

	static register_read_write<0x401F857C> QTIMER3_TIMER0_SELECT_INPUT;
	static register_read_write<0x401F8580> QTIMER3_TIMER1_SELECT_INPUT;
	static register_read_write<0x401F8584> QTIMER3_TIMER2_SELECT_INPUT;
	static register_read_write<0x401F8588> QTIMER3_TIMER3_SELECT_INPUT;

	static register_read_write<0x401F858C> SAI1_MCLK2_SELECT_INPUT;
	static register_read_write<0x401F8590> SAI1_RX_BCLK_SELECT_INPUT;
	static register_read_write<0x401F8594> SAI1_RX_DATA0_SELECT_INPUT;
	static register_read_write<0x401F8598> SAI1_RX_DATA1_SELECT_INPUT;
	static register_read_write<0x401F859C> SAI1_RX_DATA2_SELECT_INPUT;
	static register_read_write<0x401F85A0> SAI1_RX_DATA3_SELECT_INPUT;
	static register_read_write<0x401F85A4> SAI1_RX_SYNC_SELECT_INPUT;
	static register_read_write<0x401F85A8> SAI1_TX_BCLK_SELECT_INPUT;
	static register_read_write<0x401F85AC> SAI1_TX_SYNC_SELECT_INPUT;

	static register_read_write<0x401F85B0> SAI2_MCLK2_SELECT_INPUT;
	static register_read_write<0x401F85B4> SAI2_RX_BCLK_SELECT_INPUT;
	static register_read_write<0x401F85B8> SAI2_RX_DATA0_SELECT_INPUT;
	static register_read_write<0x401F85BC> SAI2_RX_SYNC_SELECT_INPUT;
	static register_read_write<0x401F85C0> SAI2_TX_BCLK_SELECT_INPUT;
	static register_read_write<0x401F85C4> SAI2_TX_SYNC_SELECT_INPUT;

	static register_read_write<0x401F85C8> SPDIF_IN_SELECT_INPUT;

	static register_read_write<0x401F85CC> USB_OTG2_OC_SELECT_INPUT;
	static register_read_write<0x401F85D0> USB_OTG1_OC_SELECT_INPUT;

	static register_read_write<0x401F85D4> USDHC1_CD_B_SELECT_INPUT;
	static register_read_write<0x401F85D8> USDHC1_WP_SELECT_INPUT;

	static register_read_write<0x401F85DC> USDHC2_CLK_SELECT_INPUT;
	static register_read_write<0x401F85E0> USDHC2_CD_B_SELECT_INPUT;
	static register_read_write<0x401F85E4> USDHC2_CMD_SELECT_INPUT;
	static register_read_write<0x401F85E8> USDHC2_DATA0_SELECT_INPUT;
	static register_read_write<0x401F85EC> USDHC2_DATA1_SELECT_INPUT;
	static register_read_write<0x401F85F0> USDHC2_DATA2_SELECT_INPUT;
	static register_read_write<0x401F85F4> USDHC2_DATA3_SELECT_INPUT;
	static register_read_write<0x401F85F8> USDHC2_DATA4_SELECT_INPUT;
	static register_read_write<0x401F85FC> USDHC2_DATA5_SELECT_INPUT;
	static register_read_write<0x401F8600> USDHC2_DATA6_SELECT_INPUT;
	static register_read_write<0x401F8604> USDHC2_DATA7_SELECT_INPUT;
	static register_read_write<0x401F8608> USDHC2_WP_SELECT_INPUT;

	static register_read_write<0x401F860C> XBAR1_IN02_SELECT_INPUT;
	static register_read_write<0x401F8610> XBAR1_IN03_SELECT_INPUT;
	static register_read_write<0x401F8614> XBAR1_IN04_SELECT_INPUT;
	static register_read_write<0x401F8618> XBAR1_IN05_SELECT_INPUT;
	static register_read_write<0x401F861C> XBAR1_IN06_SELECT_INPUT;
	static register_read_write<0x401F8620> XBAR1_IN07_SELECT_INPUT;
	static register_read_write<0x401F8624> XBAR1_IN08_SELECT_INPUT;
	static register_read_write<0x401F8628> XBAR1_IN09_SELECT_INPUT;
	static register_read_write<0x401F862C> XBAR1_IN17_SELECT_INPUT;
	static register_read_write<0x401F8630> XBAR1_IN18_SELECT_INPUT;
	static register_read_write<0x401F8634> XBAR1_IN20_SELECT_INPUT;
	static register_read_write<0x401F8638> XBAR1_IN22_SELECT_INPUT;
	static register_read_write<0x401F863C> XBAR1_IN23_SELECT_INPUT;
	static register_read_write<0x401F8640> XBAR1_IN24_SELECT_INPUT;
	static register_read_write<0x401F8644> XBAR1_IN14_SELECT_INPUT;
	static register_read_write<0x401F8648> XBAR1_IN15_SELECT_INPUT;
	static register_read_write<0x401F864C> XBAR1_IN16_SELECT_INPUT;
	static register_read_write<0x401F8650> XBAR1_IN25_SELECT_INPUT;
	static register_read_write<0x401F8654> XBAR1_IN19_SELECT_INPUT;
	static register_read_write<0x401F8658> XBAR1_IN21_SELECT_INPUT;

	static register_read_write<0x401F870C> ENET2_IPG_CLK_RMII_SELECT_INPUT;
	static register_read_write<0x401F8710> ENET2_IPP_IND_MAC0_MDIO_SELECT_INPUT;
	static register_read_write<0x401F8714> ENET2_IPP_IND_MAC0_RXDATA_SELECT_INPUT_0;
	static register_read_write<0x401F8718> ENET2_IPP_IND_MAC0_RXDATA_SELECT_INPUT_1;
	static register_read_write<0x401F871C> ENET2_IPP_IND_MAC0_RXEN_SELECT_INPUT;
	static register_read_write<0x401F8720> ENET2_IPP_IND_MAC0_RXERR_SELECT_INPUT;
	static register_read_write<0x401F8724> ENET2_IPP_IND_MAC0_TIMER_SELECT_INPUT_0;
	static register_read_write<0x401F8728> ENET2_IPP_IND_MAC0_TXCLK_SELECT_INPUT;

	static register_read_write<0x401F872C> FLEXSPI2_IPP_IND_DQS_FA_SELECT_INPUT;
	static register_read_write<0x401F8730> FLEXSPI2_IPP_IND_IO_FA_BIT0_SELECT_INPUT;
	static register_read_write<0x401F8734> FLEXSPI2_IPP_IND_IO_FA_BIT1_SELECT_INPUT;
	static register_read_write<0x401F8738> FLEXSPI2_IPP_IND_IO_FA_BIT2_SELECT_INPUT;
	static register_read_write<0x401F873C> FLEXSPI2_IPP_IND_IO_FA_BIT3_SELECT_INPUT;
	static register_read_write<0x401F8740> FLEXSPI2_IPP_IND_IO_FB_BIT0_SELECT_INPUT;
	static register_read_write<0x401F8744> FLEXSPI2_IPP_IND_IO_FB_BIT1_SELECT_INPUT;
	static register_read_write<0x401F8748> FLEXSPI2_IPP_IND_IO_FB_BIT2_SELECT_INPUT;
	static register_read_write<0x401F874C> FLEXSPI2_IPP_IND_IO_FB_BIT3_SELECT_INPUT;
	static register_read_write<0x401F8750> FLEXSPI2_IPP_IND_SCK_FA_SELECT_INPUT;
	static register_read_write<0x401F8754> FLEXSPI2_IPP_IND_SCK_FB_SELECT_INPUT;

	static register_read_write<0x401F8758> GPT1_IPP_IND_CAPIN1_SELECT_INPUT;
	static register_read_write<0x401F875C> GPT1_IPP_IND_CAPIN2_SELECT_INPUT;
	static register_read_write<0x401F8760> GPT1_IPP_IND_CLKIN_SELECT_INPUT;

	static register_read_write<0x401F8764> GPT2_IPP_IND_CAPIN1_SELECT_INPUT;
	static register_read_write<0x401F8768> GPT2_IPP_IND_CAPIN2_SELECT_INPUT;
	static register_read_write<0x401F876C> GPT2_IPP_IND_CLKIN_SELECT_INPUT;

	static register_read_write<0x401F8770> SAI3_IPG_CLK_SAI_MCLK_SELECT_INPUT_2;
	static register_read_write<0x401F8774> SAI3_IPP_IND_SAI_RXBCLK_SELECT_INPUT;
	static register_read_write<0x401F8778> SAI3_IPP_IND_SAI_RXDATA_SELECT_INPUT_0;
	static register_read_write<0x401F877C> SAI3_IPP_IND_SAI_RXSYNC_SELECT_INPUT;
	static register_read_write<0x401F8780> SAI3_IPP_IND_SAI_TXBCLK_SELECT_INPUT;
	static register_read_write<0x401F8784> SAI3_IPP_IND_SAI_TXSYNC_SELECT_INPUT;

	static register_read_write<0x401F8788> SEMC_I_IPP_IND_DQS4_SELECT_INPUT;

	static register_read_write<0x401F878C> CANFD_IPP_IND_CANRX_SELECT_INPUT;
} // namespace nxp::imxrt1060::iomuxc

#pragma pack(pop)
