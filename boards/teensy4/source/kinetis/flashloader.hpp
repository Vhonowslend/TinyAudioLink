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
#ifndef TEENSY41_FLASHLOADER_H
#define TEENSY41_FLASHLOADER_H

// This is critical, so ensure it's byte aligned.
#pragma pack(push, 1)

#include <inttypes.h>

#ifndef TEENSY_FLASH_SIZE
#define TEENSY_FLASH_SIZE 0x00800000
#endif

// Defaults are for loading from NAND Flash. It can support NOR Flash and SD/eMMC.
struct flashLoader_t {
	// 0x000 Tag
	uint32_t tag = 0x42464346; // FCFB
	// 0x004 Version
	uint32_t version = 0x56010000; // V,1,0,0
	// 0x008 Reserved
	uint32_t __reserved0 = 0;
	// 0x00C Read Sample Clock Source
	// - 0 Internal Loopback
	// - 1 Loopback from DQS Pad
	// - 3 Flash provided DQS
	uint8_t readSampleClkSrc = 0x1;
	// 0x00D Serial Flash CS Hold Time
	uint8_t csHoldTime = 0x3;
	// 0x00E Serial Flash CS Setup Time
	uint8_t csSetupTime = 0x3;
	// 0x00F Column Address Width
	// - 3 HyperFlash/HyperRAM
	// - 12/13 Serial NAND, see Datasheet
	// - 0 Anything else
	uint8_t columnAdressWidth = 0;
	// 0x010 Device Mode Configuration Feature
	uint8_t deviceModeCfgEnable = 0;
	// 0x011 Device Mode Type
	uint8_t deviceModeType = 0;
	// 0x012 Wait time for all configuration commands, in 100µs steps.
	// - 0 Use read status command.
	// - * Apply delay for commands.
	uint16_t waitTimeCfgCommands = 0;
	// 0x014 Device Mode Configuration Sequence
	uint32_t deviceModeSeq = 0;
	// 0x018
	uint32_t deviceModeArg = 0;
	// 0x01C
	uint8_t configCmdEnable = 0;
	// 0x01D
	uint8_t configModeType[3] = {0};
	// 0x020
	uint8_t configCmdSeqs[12] = {0};
	// 0x02C Reserved
	uint32_t __reserved1 = 0;
	// 0x030
	uint8_t cfgCmdArgs[12] = {0};
	// 0x03C Reserved
	uint32_t __reserved2 = 0;
	// 0x040
	uint32_t controllerMiscOption = 0;
	// 0x044 Device Type
	// - 1 Serial NOR (FlexSPI NOR)
	// - 2 Serial NAND (FlexSPI NAND)
	uint8_t deviceType = 1;
	// 0x045 Flash Type
	// - 1 Single Pad
	// - 2 Dual Pad
	// - 4 Quad Pad
	// - 8 Octal Pad
	// - Anything else is invalid and crashes.
	uint8_t sflashPadType = 4; // Teensy 4.1 is Quad Pad
	// 0x046
	uint8_t serialClkFreq = 8;
	// 0x047
	// - 0 Use pre-defined LUT Sequence Index and Number
	// - 1 Use LUT parameters provided with lutCustomSeq.
	uint8_t lutCustomSeqEnable = 0;
	// 0x048 Reserved
	uint32_t __reserved3[2] = {0};
	// 0x050 Flash Memory Size
	uint32_t sflashA1Size = TEENSY_FLASH_SIZE;
	// 0x054
	uint32_t sflashA2Size = 0;
	// 0x058
	uint32_t sflashB1Size = 0;
	// 0x05C
	uint32_t sflashB2Size = 0;
	// 0x060
	uint32_t csPadSettingOverride = 0;
	// 0x064
	uint32_t sclkPadSettingOverride = 0;
	// 0x068
	uint32_t dataPadSettingOverride = 0;
	// 0x06C
	uint32_t dqsPadSettingOverride = 0;
	// 0x070
	uint32_t timeoutInMs = 0;
	// 0x074
	uint32_t commandInterval = 0;
	// 0x078
	uint32_t dataValidTime = 0;
	// 0x07C
	uint16_t busyOffset = 0;
	// 0x07E
	uint16_t busyBitPolarity = 0;
	// 0x080 Look-Up Table (256 bytes)
	uint32_t lookUpTable[64] = {
		// 0x080
		0x0A1804EB,
		0x26043206,
		0,
		0,
		// 0x090
		0x24040405,
		0,
		0,
		0,
		// 0x0A0
		0,
		0,
		0,
		0,
		// 0x0B0
		0x00000406,
		0,
		0,
		0,
		// 0x0C0
		0,
		0,
		0,
		0,
		// 0x0D0
		0x08180420,
		0,
		0,
		0,
		// 0x0E0
		0,
		0,
		0,
		0,
		// 0x0F0
		0,
		0,
		0,
		0,
		// 0x100
		0x081804D8,
		0,
		0,
		0,
		// 0x110
		0x08180402,
		0x00002004,
		0,
		0,
		// 0x120
		0,
		0,
		0,
		0,
		// 0x130
		0x00000460,
		0,
		0,
		0,
		// 0x140
		0,
		0,
		0,
		0,
		// 0x150
		0,
		0,
		0,
		// 0x160
		0,
		0,
		0,
		0,
		// 0x170
		0,
		0,
		0,
		0,
	};
	// 0x180
	uint32_t lutCustomSeq[12] = {
		// 0x180
		0,
		0,
		0,
		0,
		// 0x190
		0,
		0,
		0,
		0,
		// 0x1A0
		0,
		0,
		0,
		0,
	};
	// 0x1B0 Reserved
	uint32_t __reserved4[4] = {0};
	// 0x1C0 Flash Page Size
	uint32_t pageSize = 256;
	// 0x1C4 Flash Sector Size
	uint32_t sectorSize = 4096;
	// 0x1C8 IP Command Clock Frequency
	uint8_t ipCmdSerialClkFreq = 1;
	// 0x1C9 Is the Sector and Block size identical?
	// - 0 No (false)
	// - 1 Yes (true)
	uint8_t isUniformBlockSize = 0;
	// 0x1CA Reserved
	uint16_t __reserved5 = 0;
	// 0x1CC Serial NOR Flash Type
	// - 0 Extended SPI
	// - 1 HyperBUS
	// - 2 Octal DDR
	uint8_t serialNorType = 0;
	// 0x1CD Reserved
	uint8_t __reserved6 = 0;
	// 0x1CE
	uint8_t halfClkForNonReadCmd = 0;
	// 0x1CF Reserved
	uint8_t __reserved7 = 0;
	// 0x1D0 Flash Block Size (see isUniformBlockSize, sectorSize and pageSize)
	uint32_t blockSize = 0x00010000;
	// 0x1D4 Reserved
	uint32_t __reserved8[11] = {0};
};
static constexpr std::size_t falshLoader_sz = 0x200;

#pragma pack(pop)
#endif
