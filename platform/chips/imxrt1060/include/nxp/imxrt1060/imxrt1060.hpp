#pragma once
#include <register.hpp>
#import "cinttypes"
#import "cstddef"

namespace nxp::imxrt1060 {
	static register_read_write<0x400A4000> IOMUXC_SNVS_GPR0;
	static register_read_write<0x400A4004> IOMUXC_SNVS_GPR1;
	static register_read_write<0x400A4008> IOMUXC_SNVS_GPR2;
	static register_read_write<0x400A400C> IOMUXC_SNVS_GPR3;

	static register_read_write<0x400A8000> IOMUXC_SNVS_SW_MUX_CTL_PAD_WAKEUP;
	static register_read_write<0x400A8004> IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_ON_REQ;
	static register_read_write<0x400A8008> IOMUXC_SNVS_SW_MUX_CTL_PAD_PMIC_STBY_REQ;
	static register_read_write<0x400A800C> IOMUXC_SNVS_SW_PAD_CTL_PAD_TEST_MODE;
	static register_read_write<0x400A8010> IOMUXC_SNVS_SW_PAD_CTL_PAD_POR_B;
	static register_read_write<0x400A8014> IOMUXC_SNVS_SW_PAD_CTL_PAD_ONOFF;
	static register_read_write<0x400A8018> IOMUXC_SNVS_SW_PAD_CTL_PAD_WAKEUP;
	static register_read_write<0x400A801C> IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_ON_REQ;
	static register_read_write<0x400A8020> IOMUXC_SNVS_SW_PAD_CTL_PAD_PMIC_STBY_REQ;

	static register_read_write<0x400AC000> IOMUXC_GPR0;
	static register_read_write<0x400AC004> IOMUXC_GPR1;
	static register_read_write<0x400AC008> IOMUXC_GPR2;
	static register_read_write<0x400AC00C> IOMUXC_GPR3;
	static register_read_write<0x400AC010> IOMUXC_GPR4;
	static register_read_write<0x400AC014> IOMUXC_GPR5;
	static register_read_write<0x400AC018> IOMUXC_GPR6;
	static register_read_write<0x400AC01C> IOMUXC_GPR7;
	static register_read_write<0x400AC020> IOMUXC_GPR8;
	static register_read_write<0x400AC024> IOMUXC_GPR9;
	static register_read_write<0x400AC028> IOMUXC_GPR10;
	static register_read_write<0x400AC02C> IOMUXC_GPR11;
	static register_read_write<0x400AC030> IOMUXC_GPR12;
	static register_read_write<0x400AC034> IOMUXC_GPR13;
	static register_read_write<0x400AC038> IOMUXC_GPR14;
	static register_read_write<0x400AC03C> IOMUXC_GPR15;
	static register_read_write<0x400AC040> IOMUXC_GPR16;
	static register_read_write<0x400AC044> IOMUXC_GPR17;
	static register_read_write<0x400AC048> IOMUXC_GPR18;
	static register_read_write<0x400AC04C> IOMUXC_GPR19;
	static register_read_write<0x400AC050> IOMUXC_GPR20;
	static register_read_write<0x400AC054> IOMUXC_GPR21;
	static register_read_write<0x400AC058> IOMUXC_GPR22;
	static register_read_write<0x400AC05C> IOMUXC_GPR23;
	static register_read_write<0x400AC060> IOMUXC_GPR24;
	static register_read_write<0x400AC064> IOMUXC_GPR25;
	static register_read_write<0x400AC068> IOMUXC_GPR26;
	static register_read_write<0x400AC06C> IOMUXC_GPR27;
	static register_read_write<0x400AC070> IOMUXC_GPR28;
	static register_read_write<0x400AC074> IOMUXC_GPR29;
	static register_read_write<0x400AC078> IOMUXC_GPR30;
	static register_read_write<0x400AC07C> IOMUXC_GPR31;
	static register_read_write<0x400AC080> IOMUXC_GPR32;
	static register_read_write<0x400AC084> IOMUXC_GPR33;
	static register_read_write<0x400AC088> IOMUXC_GPR34;

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

	static register_read_write<0x401F8014> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_00;
	static register_read_write<0x401F8018> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_01;
	static register_read_write<0x401F801C> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_02;
	static register_read_write<0x401F8020> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_03;
	static register_read_write<0x401F8024> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_04;
	static register_read_write<0x401F8028> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_05;
	static register_read_write<0x401F802C> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_06;
	static register_read_write<0x401F8030> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_07;
	static register_read_write<0x401F8034> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_08;
	static register_read_write<0x401F8038> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_09;
	static register_read_write<0x401F803C> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_10;
	static register_read_write<0x401F8040> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_11;
	static register_read_write<0x401F8044> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_12;
	static register_read_write<0x401F8048> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_13;
	static register_read_write<0x401F804C> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_14;
	static register_read_write<0x401F8050> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_15;
	static register_read_write<0x401F8054> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_16;
	static register_read_write<0x401F8058> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_17;
	static register_read_write<0x401F805C> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_18;
	static register_read_write<0x401F8060> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_19;
	static register_read_write<0x401F8064> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_20;
	static register_read_write<0x401F8068> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_21;
	static register_read_write<0x401F806C> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_22;
	static register_read_write<0x401F8070> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_23;
	static register_read_write<0x401F8074> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_24;
	static register_read_write<0x401F8078> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_25;
	static register_read_write<0x401F807C> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_26;
	static register_read_write<0x401F8080> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_27;
	static register_read_write<0x401F8084> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_28;
	static register_read_write<0x401F8088> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_29;
	static register_read_write<0x401F808C> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_30;
	static register_read_write<0x401F8090> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_31;
	static register_read_write<0x401F8094> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_32;
	static register_read_write<0x401F8098> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_33;
	static register_read_write<0x401F809C> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_34;
	static register_read_write<0x401F80A0> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_35;
	static register_read_write<0x401F80A4> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_36;
	static register_read_write<0x401F80A8> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_37;
	static register_read_write<0x401F80AC> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_38;
	static register_read_write<0x401F80B0> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_39;
	static register_read_write<0x401F80B4> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_40;
	static register_read_write<0x401F80B8> IOMUXC_SW_MUX_CTL_PAD_GPIO_EMC_41;

	static register_read_write<0x401F80BC> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_00;
	static register_read_write<0x401F80C0> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_01;
	static register_read_write<0x401F80C4> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_02;
	static register_read_write<0x401F80C8> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_03;
	static register_read_write<0x401F80CC> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_04;
	static register_read_write<0x401F80D0> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_05;
	static register_read_write<0x401F80D4> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_06;
	static register_read_write<0x401F80D8> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_07;
	static register_read_write<0x401F80DC> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_08;
	static register_read_write<0x401F80E0> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_09;
	static register_read_write<0x401F80E4> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_10;
	static register_read_write<0x401F80E8> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_11;
	static register_read_write<0x401F80EC> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_12;
	static register_read_write<0x401F80F0> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_13;
	static register_read_write<0x401F80F4> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_14;
	static register_read_write<0x401F80F8> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B0_15;

	static register_read_write<0x401F80FC> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_00;
	static register_read_write<0x401F8100> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_01;
	static register_read_write<0x401F8104> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_02;
	static register_read_write<0x401F8108> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_03;
	static register_read_write<0x401F810C> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_04;
	static register_read_write<0x401F8110> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_05;
	static register_read_write<0x401F8114> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_06;
	static register_read_write<0x401F8118> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_07;
	static register_read_write<0x401F811C> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_08;
	static register_read_write<0x401F8120> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_09;
	static register_read_write<0x401F8124> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_10;
	static register_read_write<0x401F8128> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_11;
	static register_read_write<0x401F812C> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_12;
	static register_read_write<0x401F8130> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_13;
	static register_read_write<0x401F8134> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_14;
	static register_read_write<0x401F8138> IOMUXC_SW_MUX_CTL_PAD_GPIO_AD_B1_15;

	static register_read_write<0x401F813C> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_00;
	static register_read_write<0x401F8140> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_01;
	static register_read_write<0x401F8144> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_02;
	static register_read_write<0x401F8148> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_03;
	static register_read_write<0x401F814C> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_04;
	static register_read_write<0x401F8150> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_05;
	static register_read_write<0x401F8154> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_06;
	static register_read_write<0x401F8158> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_07;
	static register_read_write<0x401F815C> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_08;
	static register_read_write<0x401F8160> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_09;
	static register_read_write<0x401F8164> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_10;
	static register_read_write<0x401F8168> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_11;
	static register_read_write<0x401F816C> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_12;
	static register_read_write<0x401F8170> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_13;
	static register_read_write<0x401F8174> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_14;
	static register_read_write<0x401F8178> IOMUXC_SW_MUX_CTL_PAD_GPIO_B0_15;

	static register_read_write<0x401F817C> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_00;
	static register_read_write<0x401F8180> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_01;
	static register_read_write<0x401F8184> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_02;
	static register_read_write<0x401F8188> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_03;
	static register_read_write<0x401F818C> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_04;
	static register_read_write<0x401F8190> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_05;
	static register_read_write<0x401F8194> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_06;
	static register_read_write<0x401F8198> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_07;
	static register_read_write<0x401F819C> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_08;
	static register_read_write<0x401F81A0> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_09;
	static register_read_write<0x401F81A4> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_10;
	static register_read_write<0x401F81A8> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_11;
	static register_read_write<0x401F81AC> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_12;
	static register_read_write<0x401F81B0> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_13;
	static register_read_write<0x401F81B4> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_14;
	static register_read_write<0x401F81B8> IOMUXC_SW_MUX_CTL_PAD_GPIO_B1_15;

	static register_read_write<0x401F81BC> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_00;
	static register_read_write<0x401F81C0> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_01;
	static register_read_write<0x401F81C4> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_02;
	static register_read_write<0x401F81C8> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_03;
	static register_read_write<0x401F81CC> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_04;
	static register_read_write<0x401F81D0> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B0_05;

	static register_read_write<0x401F81D4> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_00;
	static register_read_write<0x401F81D8> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_01;
	static register_read_write<0x401F81DC> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_02;
	static register_read_write<0x401F81E0> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_03;
	static register_read_write<0x401F81E4> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_04;
	static register_read_write<0x401F81E8> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_05;
	static register_read_write<0x401F81EC> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_06;
	static register_read_write<0x401F81F0> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_07;
	static register_read_write<0x401F81F4> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_08;
	static register_read_write<0x401F81F8> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_09;
	static register_read_write<0x401F81FC> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_10;
	static register_read_write<0x401F8200> IOMUXC_SW_MUX_CTL_PAD_GPIO_SD_B1_11;

	static register_read_write<0x401F8204> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_00;
	static register_read_write<0x401F8208> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_01;
	static register_read_write<0x401F820C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_02;
	static register_read_write<0x401F8210> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_03;
	static register_read_write<0x401F8214> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_04;
	static register_read_write<0x401F8218> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_05;
	static register_read_write<0x401F821C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_06;
	static register_read_write<0x401F8220> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_07;
	static register_read_write<0x401F8224> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_08;
	static register_read_write<0x401F8228> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_09;
	static register_read_write<0x401F822C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_10;
	static register_read_write<0x401F8230> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_11;
	static register_read_write<0x401F8234> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_12;
	static register_read_write<0x401F8238> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_13;
	static register_read_write<0x401F823C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_14;
	static register_read_write<0x401F8240> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_15;
	static register_read_write<0x401F8244> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_16;
	static register_read_write<0x401F8248> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_17;
	static register_read_write<0x401F824C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_18;
	static register_read_write<0x401F8250> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_19;
	static register_read_write<0x401F8254> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_20;
	static register_read_write<0x401F8258> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_21;
	static register_read_write<0x401F825C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_22;
	static register_read_write<0x401F8260> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_23;
	static register_read_write<0x401F8264> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_24;
	static register_read_write<0x401F8268> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_25;
	static register_read_write<0x401F826C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_26;
	static register_read_write<0x401F8270> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_27;
	static register_read_write<0x401F8274> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_28;
	static register_read_write<0x401F8278> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_29;
	static register_read_write<0x401F827C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_30;
	static register_read_write<0x401F8280> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_31;
	static register_read_write<0x401F8284> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_32;
	static register_read_write<0x401F8288> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_33;
	static register_read_write<0x401F828C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_34;
	static register_read_write<0x401F8290> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_35;
	static register_read_write<0x401F8294> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_36;
	static register_read_write<0x401F8298> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_37;
	static register_read_write<0x401F829C> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_38;
	static register_read_write<0x401F82A0> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_39;
	static register_read_write<0x401F82A4> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_40;
	static register_read_write<0x401F82A8> IOMUXC_SW_PAD_CTL_PAD_GPIO_EMC_41;

	static register_read_write<0x401F82AC> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_00;
	static register_read_write<0x401F82B0> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_01;
	static register_read_write<0x401F82B4> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_02;
	static register_read_write<0x401F82B8> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_03;
	static register_read_write<0x401F82BC> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_04;
	static register_read_write<0x401F82C0> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_05;
	static register_read_write<0x401F82C4> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_06;
	static register_read_write<0x401F82C8> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_07;
	static register_read_write<0x401F82CC> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_08;
	static register_read_write<0x401F82D0> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_09;
	static register_read_write<0x401F82D4> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_10;
	static register_read_write<0x401F82D8> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_11;
	static register_read_write<0x401F82DC> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_12;
	static register_read_write<0x401F82E0> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_13;
	static register_read_write<0x401F82E4> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_14;
	static register_read_write<0x401F82E8> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B0_15;

	static register_read_write<0x401F82EC> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_00;
	static register_read_write<0x401F82F0> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_01;
	static register_read_write<0x401F82F4> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_02;
	static register_read_write<0x401F82F8> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_03;
	static register_read_write<0x401F82FC> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_04;
	static register_read_write<0x401F8300> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_05;
	static register_read_write<0x401F8304> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_06;
	static register_read_write<0x401F8308> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_07;
	static register_read_write<0x401F830C> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_08;
	static register_read_write<0x401F8310> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_09;
	static register_read_write<0x401F8314> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_10;
	static register_read_write<0x401F8318> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_11;
	static register_read_write<0x401F831C> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_12;
	static register_read_write<0x401F8320> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_13;
	static register_read_write<0x401F8324> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_14;
	static register_read_write<0x401F8328> IOMUXC_SW_PAD_CTL_PAD_GPIO_AD_B1_15;

	static register_read_write<0x401F832C> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_00;
	static register_read_write<0x401F8330> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_01;
	static register_read_write<0x401F8334> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_02;
	static register_read_write<0x401F8338> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_03;
	static register_read_write<0x401F833C> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_04;
	static register_read_write<0x401F8340> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_05;
	static register_read_write<0x401F8344> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_06;
	static register_read_write<0x401F8348> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_07;
	static register_read_write<0x401F834C> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_08;
	static register_read_write<0x401F8350> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_09;
	static register_read_write<0x401F8354> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_10;
	static register_read_write<0x401F8358> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_11;
	static register_read_write<0x401F835C> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_12;
	static register_read_write<0x401F8360> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_13;
	static register_read_write<0x401F8364> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_14;
	static register_read_write<0x401F8368> IOMUXC_SW_PAD_CTL_PAD_GPIO_B0_15;

	static register_read_write<0x401F836C> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_00;
	static register_read_write<0x401F8370> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_01;
	static register_read_write<0x401F8374> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_02;
	static register_read_write<0x401F8378> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_03;
	static register_read_write<0x401F837C> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_04;
	static register_read_write<0x401F8380> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_05;
	static register_read_write<0x401F8384> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_06;
	static register_read_write<0x401F8388> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_07;
	static register_read_write<0x401F838C> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_08;
	static register_read_write<0x401F8390> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_09;
	static register_read_write<0x401F8394> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_10;
	static register_read_write<0x401F8398> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_11;
	static register_read_write<0x401F839C> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_12;
	static register_read_write<0x401F83A0> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_13;
	static register_read_write<0x401F83A4> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_14;
	static register_read_write<0x401F83A8> IOMUXC_SW_PAD_CTL_PAD_GPIO_B1_15;

	static register_read_write<0x401F83AC> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_00;
	static register_read_write<0x401F83B0> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_01;
	static register_read_write<0x401F83B4> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_02;
	static register_read_write<0x401F83B8> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_03;
	static register_read_write<0x401F83BC> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_04;
	static register_read_write<0x401F83C0> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B0_05;

	static register_read_write<0x401F83C4> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_00;
	static register_read_write<0x401F83C8> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_01;
	static register_read_write<0x401F83CC> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_02;
	static register_read_write<0x401F83D0> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_03;
	static register_read_write<0x401F83D4> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_04;
	static register_read_write<0x401F83D8> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_05;
	static register_read_write<0x401F83DC> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_06;
	static register_read_write<0x401F83E0> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_07;
	static register_read_write<0x401F83E4> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_08;
	static register_read_write<0x401F83E8> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_09;
	static register_read_write<0x401F83EC> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_10;
	static register_read_write<0x401F83F0> IOMUXC_SW_PAD_CTL_PAD_GPIO_SD_B1_11;

	static register_read_write<0x401F83F4> IOMUXC_ANATOP_USB_OTG1_ID_SELECT_INPUT;
	static register_read_write<0x401F83F8> IOMUXC_ANATOP_USB_OTG2_ID_SELECT_INPUT;
	static register_read_write<0x401F83FC> IOMUXC_CCM_PMIC_READY_SELECT_INPUT;

	static register_read_write<0x401F8400> IOMUXC_CSI_DATA02_SELECT_INPUT;
	static register_read_write<0x401F8404> IOMUXC_CSI_DATA03_SELECT_INPUT;
	static register_read_write<0x401F8408> IOMUXC_CSI_DATA04_SELECT_INPUT;
	static register_read_write<0x401F840C> IOMUXC_CSI_DATA05_SELECT_INPUT;
	static register_read_write<0x401F8410> IOMUXC_CSI_DATA06_SELECT_INPUT;
	static register_read_write<0x401F8414> IOMUXC_CSI_DATA07_SELECT_INPUT;
	static register_read_write<0x401F8418> IOMUXC_CSI_DATA08_SELECT_INPUT;
	static register_read_write<0x401F841C> IOMUXC_CSI_DATA09_SELECT_INPUT;
	static register_read_write<0x401F8420> IOMUXC_CSI_HSYNC_SELECT_INPUT;
	static register_read_write<0x401F8424> IOMUXC_CSI_PIXCLK_SELECT_INPUT;
	static register_read_write<0x401F8428> IOMUXC_CSI_VSYNC_SELECT_INPUT;

	static register_read_write<0x401F842C> IOMUXC_ENET_IPG_CLK_RMII_SELECT_INPUT;
	static register_read_write<0x401F8430> IOMUXC_ENET_MDIO_SELECT_INPUT;
	static register_read_write<0x401F8434> IOMUXC_ENET0_RXDATA_SELECT_INPUT;
	static register_read_write<0x401F8438> IOMUXC_ENET1_RXDATA_SELECT_INPUT;
	static register_read_write<0x401F843C> IOMUXC_ENET_RXEN_SELECT_INPUT;
	static register_read_write<0x401F8440> IOMUXC_ENET_RXERR_SELECT_INPUT;
	static register_read_write<0x401F8444> IOMUXC_ENET0_TIMER_SELECT_INPUT;
	static register_read_write<0x401F8448> IOMUXC_ENET_TXCLK_SELECT_INPUT;

	static register_read_write<0x401F844C> IOMUXC_FLEXCAN1_RX_SELECT_INPUT;
	static register_read_write<0x401F8450> IOMUXC_FLEXCAN2_RX_SELECT_INPUT;

	static register_read_write<0x401F8454> IOMUXC_FLEXPWM1_PWMA3_SELECT_INPUT;
	static register_read_write<0x401F8458> IOMUXC_FLEXPWM1_PWMA0_SELECT_INPUT;
	static register_read_write<0x401F845C> IOMUXC_FLEXPWM1_PWMA1_SELECT_INPUT;
	static register_read_write<0x401F8460> IOMUXC_FLEXPWM1_PWMA2_SELECT_INPUT;
	static register_read_write<0x401F8464> IOMUXC_FLEXPWM1_PWMB3_SELECT_INPUT;
	static register_read_write<0x401F8468> IOMUXC_FLEXPWM1_PWMB0_SELECT_INPUT;
	static register_read_write<0x401F846C> IOMUXC_FLEXPWM1_PWMB1_SELECT_INPUT;
	static register_read_write<0x401F8470> IOMUXC_FLEXPWM1_PWMB2_SELECT_INPUT;

	static register_read_write<0x401F8474> IOMUXC_FLEXPWM2_PWMA3_SELECT_INPUT;
	static register_read_write<0x401F8478> IOMUXC_FLEXPWM2_PWMA0_SELECT_INPUT;
	static register_read_write<0x401F847C> IOMUXC_FLEXPWM2_PWMA1_SELECT_INPUT;
	static register_read_write<0x401F8480> IOMUXC_FLEXPWM2_PWMA2_SELECT_INPUT;
	static register_read_write<0x401F8484> IOMUXC_FLEXPWM2_PWMB3_SELECT_INPUT;
	static register_read_write<0x401F8488> IOMUXC_FLEXPWM2_PWMB0_SELECT_INPUT;
	static register_read_write<0x401F848C> IOMUXC_FLEXPWM2_PWMB1_SELECT_INPUT;
	static register_read_write<0x401F8490> IOMUXC_FLEXPWM2_PWMB2_SELECT_INPUT;

	static register_read_write<0x401F8494> IOMUXC_FLEXPWM4_PWMA0_SELECT_INPUT;
	static register_read_write<0x401F8498> IOMUXC_FLEXPWM4_PWMA1_SELECT_INPUT;
	static register_read_write<0x401F849C> IOMUXC_FLEXPWM4_PWMA2_SELECT_INPUT;
	static register_read_write<0x401F84A0> IOMUXC_FLEXPWM4_PWMA3_SELECT_INPUT;

	static register_read_write<0x401F84A4> IOMUXC_FLEXSPIA_DQS_SELECT_INPUT;
	static register_read_write<0x401F84A8> IOMUXC_FLEXSPIA_DATA0_SELECT_INPUT;
	static register_read_write<0x401F84AC> IOMUXC_FLEXSPIA_DATA1_SELECT_INPUT;
	static register_read_write<0x401F84B0> IOMUXC_FLEXSPIA_DATA2_SELECT_INPUT;
	static register_read_write<0x401F84B4> IOMUXC_FLEXSPIA_DATA3_SELECT_INPUT;

	static register_read_write<0x401F84B8> IOMUXC_FLEXSPIB_DATA0_SELECT_INPUT;
	static register_read_write<0x401F84BC> IOMUXC_FLEXSPIB_DATA1_SELECT_INPUT;
	static register_read_write<0x401F84C0> IOMUXC_FLEXSPIB_DATA2_SELECT_INPUT;
	static register_read_write<0x401F84C4> IOMUXC_FLEXSPIB_DATA3_SELECT_INPUT;

	static register_read_write<0x401F84C8> IOMUXC_FLEXSPIA_SCK_SELECT_INPUT;

	static register_read_write<0x401F84CC> IOMUXC_LPI2C1_SCL_SELECT_INPUT;
	static register_read_write<0x401F84D0> IOMUXC_LPI2C1_SDA_SELECT_INPUT;
	static register_read_write<0x401F84D4> IOMUXC_LPI2C2_SCL_SELECT_INPUT;
	static register_read_write<0x401F84D8> IOMUXC_LPI2C2_SDA_SELECT_INPUT;
	static register_read_write<0x401F84DC> IOMUXC_LPI2C3_SCL_SELECT_INPUT;
	static register_read_write<0x401F84E0> IOMUXC_LPI2C3_SDA_SELECT_INPUT;
	static register_read_write<0x401F84E4> IOMUXC_LPI2C4_SCL_SELECT_INPUT;
	static register_read_write<0x401F84E8> IOMUXC_LPI2C4_SDA_SELECT_INPUT;

	static register_read_write<0x401F84EC> IOMUXC_LPSPI1_PCS0_SELECT_INPUT;
	static register_read_write<0x401F84F0> IOMUXC_LPSPI1_SCK_SELECT_INPUT;
	static register_read_write<0x401F84F4> IOMUXC_LPSPI1_SDI_SELECT_INPUT;
	static register_read_write<0x401F84F8> IOMUXC_LPSPI1_SDO_SELECT_INPUT;

	static register_read_write<0x401F84FC> IOMUXC_LPSPI2_PCS0_SELECT_INPUT;
	static register_read_write<0x401F8500> IOMUXC_LPSPI2_SCK_SELECT_INPUT;
	static register_read_write<0x401F8504> IOMUXC_LPSPI2_SDI_SELECT_INPUT;
	static register_read_write<0x401F8508> IOMUXC_LPSPI2_SDO_SELECT_INPUT;

	static register_read_write<0x401F850C> IOMUXC_LPSPI3_PCS0_SELECT_INPUT;
	static register_read_write<0x401F8510> IOMUXC_LPSPI3_SCK_SELECT_INPUT;
	static register_read_write<0x401F8514> IOMUXC_LPSPI3_SDI_SELECT_INPUT;
	static register_read_write<0x401F8518> IOMUXC_LPSPI3_SDO_SELECT_INPUT;

	static register_read_write<0x401F851C> IOMUXC_LPSPI4_PCS0_SELECT_INPUT;
	static register_read_write<0x401F8520> IOMUXC_LPSPI4_SCK_SELECT_INPUT;
	static register_read_write<0x401F8524> IOMUXC_LPSPI4_SDI_SELECT_INPUT;
	static register_read_write<0x401F8528> IOMUXC_LPSPI4_SDO_SELECT_INPUT;

	static register_read_write<0x401F852C> IOMUXC_LPUART2_RX_SELECT_INPUT;
	static register_read_write<0x401F8530> IOMUXC_LPUART2_TX_SELECT_INPUT;

	static register_read_write<0x401F8534> IOMUXC_LPUART3_CTS_B_SELECT_INPUT;
	static register_read_write<0x401F8538> IOMUXC_LPUART3_RX_SELECT_INPUT;
	static register_read_write<0x401F853C> IOMUXC_LPUART3_TX_SELECT_INPUT;

	static register_read_write<0x401F8540> IOMUXC_LPUART4_RX_SELECT_INPUT;
	static register_read_write<0x401F8544> IOMUXC_LPUART4_TX_SELECT_INPUT;

	static register_read_write<0x401F8548> IOMUXC_LPUART5_RX_SELECT_INPUT;
	static register_read_write<0x401F854C> IOMUXC_LPUART5_TX_SELECT_INPUT;

	static register_read_write<0x401F8550> IOMUXC_LPUART6_RX_SELECT_INPUT;
	static register_read_write<0x401F8554> IOMUXC_LPUART6_TX_SELECT_INPUT;

	static register_read_write<0x401F8558> IOMUXC_LPUART7_RX_SELECT_INPUT;
	static register_read_write<0x401F855C> IOMUXC_LPUART7_TX_SELECT_INPUT;

	static register_read_write<0x401F8560> IOMUXC_LPUART8_RX_SELECT_INPUT;
	static register_read_write<0x401F8564> IOMUXC_LPUART8_TX_SELECT_INPUT;

	static register_read_write<0x401F8568> IOMUXC_NMI_SELECT_INPUT;

	static register_read_write<0x401F856C> IOMUXC_QTIMER2_TIMER0_SELECT_INPUT;
	static register_read_write<0x401F8570> IOMUXC_QTIMER2_TIMER1_SELECT_INPUT;
	static register_read_write<0x401F8574> IOMUXC_QTIMER2_TIMER2_SELECT_INPUT;
	static register_read_write<0x401F8578> IOMUXC_QTIMER2_TIMER3_SELECT_INPUT;

	static register_read_write<0x401F857C> IOMUXC_QTIMER3_TIMER0_SELECT_INPUT;
	static register_read_write<0x401F8580> IOMUXC_QTIMER3_TIMER1_SELECT_INPUT;
	static register_read_write<0x401F8584> IOMUXC_QTIMER3_TIMER2_SELECT_INPUT;
	static register_read_write<0x401F8588> IOMUXC_QTIMER3_TIMER3_SELECT_INPUT;

	static register_read_write<0x401F858C> IOMUXC_SAI1_MCLK2_SELECT_INPUT;
	static register_read_write<0x401F8590> IOMUXC_SAI1_RX_BCLK_SELECT_INPUT;
	static register_read_write<0x401F8594> IOMUXC_SAI1_RX_DATA0_SELECT_INPUT;
	static register_read_write<0x401F8598> IOMUXC_SAI1_RX_DATA1_SELECT_INPUT;
	static register_read_write<0x401F859C> IOMUXC_SAI1_RX_DATA2_SELECT_INPUT;
	static register_read_write<0x401F85A0> IOMUXC_SAI1_RX_DATA3_SELECT_INPUT;
	static register_read_write<0x401F85A4> IOMUXC_SAI1_RX_SYNC_SELECT_INPUT;
	static register_read_write<0x401F85A8> IOMUXC_SAI1_TX_BCLK_SELECT_INPUT;
	static register_read_write<0x401F85AC> IOMUXC_SAI1_TX_SYNC_SELECT_INPUT;

	static register_read_write<0x401F85B0> IOMUXC_SAI2_MCLK2_SELECT_INPUT;
	static register_read_write<0x401F85B4> IOMUXC_SAI2_RX_BCLK_SELECT_INPUT;
	static register_read_write<0x401F85B8> IOMUXC_SAI2_RX_DATA0_SELECT_INPUT;
	static register_read_write<0x401F85BC> IOMUXC_SAI2_RX_SYNC_SELECT_INPUT;
	static register_read_write<0x401F85C0> IOMUXC_SAI2_TX_BCLK_SELECT_INPUT;
	static register_read_write<0x401F85C4> IOMUXC_SAI2_TX_SYNC_SELECT_INPUT;

	static register_read_write<0x401F85C8> IOMUXC_SPDIF_IN_SELECT_INPUT;

	static register_read_write<0x401F85CC> IOMUXC_USB_OTG2_OC_SELECT_INPUT;
	static register_read_write<0x401F85D0> IOMUXC_USB_OTG1_OC_SELECT_INPUT;

	static register_read_write<0x401F85D4> IOMUXC_USDHC1_CD_B_SELECT_INPUT;
	static register_read_write<0x401F85D8> IOMUXC_USDHC1_WP_SELECT_INPUT;

	static register_read_write<0x401F85DC> IOMUXC_USDHC2_CLK_SELECT_INPUT;
	static register_read_write<0x401F85E0> IOMUXC_USDHC2_CD_B_SELECT_INPUT;
	static register_read_write<0x401F85E4> IOMUXC_USDHC2_CMD_SELECT_INPUT;
	static register_read_write<0x401F85E8> IOMUXC_USDHC2_DATA0_SELECT_INPUT;
	static register_read_write<0x401F85EC> IOMUXC_USDHC2_DATA1_SELECT_INPUT;
	static register_read_write<0x401F85F0> IOMUXC_USDHC2_DATA2_SELECT_INPUT;
	static register_read_write<0x401F85F4> IOMUXC_USDHC2_DATA3_SELECT_INPUT;
	static register_read_write<0x401F85F8> IOMUXC_USDHC2_DATA4_SELECT_INPUT;
	static register_read_write<0x401F85FC> IOMUXC_USDHC2_DATA5_SELECT_INPUT;
	static register_read_write<0x401F8600> IOMUXC_USDHC2_DATA6_SELECT_INPUT;
	static register_read_write<0x401F8604> IOMUXC_USDHC2_DATA7_SELECT_INPUT;
	static register_read_write<0x401F8608> IOMUXC_USDHC2_WP_SELECT_INPUT;

	static register_read_write<0x401F860C> IOMUXC_XBAR1_IN02_SELECT_INPUT;
	static register_read_write<0x401F8610> IOMUXC_XBAR1_IN03_SELECT_INPUT;
	static register_read_write<0x401F8614> IOMUXC_XBAR1_IN04_SELECT_INPUT;
	static register_read_write<0x401F8618> IOMUXC_XBAR1_IN05_SELECT_INPUT;
	static register_read_write<0x401F861C> IOMUXC_XBAR1_IN06_SELECT_INPUT;
	static register_read_write<0x401F8620> IOMUXC_XBAR1_IN07_SELECT_INPUT;
	static register_read_write<0x401F8624> IOMUXC_XBAR1_IN08_SELECT_INPUT;
	static register_read_write<0x401F8628> IOMUXC_XBAR1_IN09_SELECT_INPUT;
	static register_read_write<0x401F862C> IOMUXC_XBAR1_IN17_SELECT_INPUT;
	static register_read_write<0x401F8630> IOMUXC_XBAR1_IN18_SELECT_INPUT;
	static register_read_write<0x401F8634> IOMUXC_XBAR1_IN20_SELECT_INPUT;
	static register_read_write<0x401F8638> IOMUXC_XBAR1_IN22_SELECT_INPUT;
	static register_read_write<0x401F863C> IOMUXC_XBAR1_IN23_SELECT_INPUT;
	static register_read_write<0x401F8640> IOMUXC_XBAR1_IN24_SELECT_INPUT;
	static register_read_write<0x401F8644> IOMUXC_XBAR1_IN14_SELECT_INPUT;
	static register_read_write<0x401F8648> IOMUXC_XBAR1_IN15_SELECT_INPUT;
	static register_read_write<0x401F864C> IOMUXC_XBAR1_IN16_SELECT_INPUT;
	static register_read_write<0x401F8650> IOMUXC_XBAR1_IN25_SELECT_INPUT;
	static register_read_write<0x401F8654> IOMUXC_XBAR1_IN19_SELECT_INPUT;
	static register_read_write<0x401F8658> IOMUXC_XBAR1_IN21_SELECT_INPUT;

	static register_read_write<0x401F870C> IOMUXC_ENET2_IPG_CLK_RMII_SELECT_INPUT;
	static register_read_write<0x401F8710> IOMUXC_ENET2_IPP_IND_MAC0_MDIO_SELECT_INPUT;
	static register_read_write<0x401F8714> IOMUXC_ENET2_IPP_IND_MAC0_RXDATA_SELECT_INPUT_0;
	static register_read_write<0x401F8718> IOMUXC_ENET2_IPP_IND_MAC0_RXDATA_SELECT_INPUT_1;
	static register_read_write<0x401F871C> IOMUXC_ENET2_IPP_IND_MAC0_RXEN_SELECT_INPUT;
	static register_read_write<0x401F8720> IOMUXC_ENET2_IPP_IND_MAC0_RXERR_SELECT_INPUT;
	static register_read_write<0x401F8724> IOMUXC_ENET2_IPP_IND_MAC0_TIMER_SELECT_INPUT_0;
	static register_read_write<0x401F8728> IOMUXC_ENET2_IPP_IND_MAC0_TXCLK_SELECT_INPUT;

	static register_read_write<0x401F872C> IOMUXC_FLEXSPI2_IPP_IND_DQS_FA_SELECT_INPUT;
	static register_read_write<0x401F8730> IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT0_SELECT_INPUT;
	static register_read_write<0x401F8734> IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT1_SELECT_INPUT;
	static register_read_write<0x401F8738> IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT2_SELECT_INPUT;
	static register_read_write<0x401F873C> IOMUXC_FLEXSPI2_IPP_IND_IO_FA_BIT3_SELECT_INPUT;
	static register_read_write<0x401F8740> IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT0_SELECT_INPUT;
	static register_read_write<0x401F8744> IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT1_SELECT_INPUT;
	static register_read_write<0x401F8748> IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT2_SELECT_INPUT;
	static register_read_write<0x401F874C> IOMUXC_FLEXSPI2_IPP_IND_IO_FB_BIT3_SELECT_INPUT;
	static register_read_write<0x401F8750> IOMUXC_FLEXSPI2_IPP_IND_SCK_FA_SELECT_INPUT;
	static register_read_write<0x401F8754> IOMUXC_FLEXSPI2_IPP_IND_SCK_FB_SELECT_INPUT;

	static register_read_write<0x401F8758> IOMUXC_GPT1_IPP_IND_CAPIN1_SELECT_INPUT;
	static register_read_write<0x401F875C> IOMUXC_GPT1_IPP_IND_CAPIN2_SELECT_INPUT;
	static register_read_write<0x401F8760> IOMUXC_GPT1_IPP_IND_CLKIN_SELECT_INPUT;

	static register_read_write<0x401F8764> IOMUXC_GPT2_IPP_IND_CAPIN1_SELECT_INPUT;
	static register_read_write<0x401F8768> IOMUXC_GPT2_IPP_IND_CAPIN2_SELECT_INPUT;
	static register_read_write<0x401F876C> IOMUXC_GPT2_IPP_IND_CLKIN_SELECT_INPUT;

	static register_read_write<0x401F8770> IOMUXC_SAI3_IPG_CLK_SAI_MCLK_SELECT_INPUT_2;
	static register_read_write<0x401F8774> IOMUXC_SAI3_IPP_IND_SAI_RXBCLK_SELECT_INPUT;
	static register_read_write<0x401F8778> IOMUXC_SAI3_IPP_IND_SAI_RXDATA_SELECT_INPUT_0;
	static register_read_write<0x401F877C> IOMUXC_SAI3_IPP_IND_SAI_RXSYNC_SELECT_INPUT;
	static register_read_write<0x401F8780> IOMUXC_SAI3_IPP_IND_SAI_TXBCLK_SELECT_INPUT;
	static register_read_write<0x401F8784> IOMUXC_SAI3_IPP_IND_SAI_TXSYNC_SELECT_INPUT;

	static register_read_write<0x401F8788> IOMUXC_SEMC_I_IPP_IND_DQS4_SELECT_INPUT;

	static register_read_write<0x401F878C> IOMUXC_CANFD_IPP_IND_CANRX_SELECT_INPUT;
} // namespace nxp::imxrt1060
