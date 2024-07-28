#include <arm/v7/nvic.hpp>
#include <chip.h>
#include <nxp/imxrt1060/bootdata.hpp>
#include <nxp/imxrt1060/imagevectortable.hpp>
#include <nxp/imxrt1060/imxrt1060.h>
#include <nxp/kinetis.hpp>
#include "board.h"

extern "C" void __main(void);
extern size_t   __flexram_bank_config; // FlexRAM Bank Configuration

extern "C" [[gnu::used, gnu::section(".flashLoader")]] const nxp::kinetis_t __flash_loader = {
	.sflashA1Size = BOARD_FLASH_SIZE,
};

extern "C" [[gnu::used, gnu::section(".bootData")]] const nxp::imxrt1060::boot_data_t __boot_data = {
	.start  = reinterpret_cast<decltype(nxp::imxrt1060::boot_data_t::start)>(BOARD_FLASH_START),
	.length = reinterpret_cast<decltype(nxp::imxrt1060::boot_data_t::length)>(BOARD_FLASH_USED),
	.plugin = 0,
};

[[gnu::used, gnu::section(".interruptVectorTable")]] arm::v7::nvic::interrupt_vector_table_t arm::v7::nvic::interrupt_vector_table = {
	.initial_stack_pointer = reinterpret_cast<const void*>(&__stack_start),
	// When using a IVT version <=4.2, the entry point is the reset interrupt, contrary to the ARM
	// documentation for this. This must be zeroed out for all other versions, but seems to do
	// nothing if it's not set to zero, as there is no way to trigger a software reset anyway.
	//
	// Additionally, __main is responsible for resetting the state of the SoC anyway, so this does
	// what we want at all times.
	.reset                  = reinterpret_cast<arm::v7::nvic::function_t>(&__main),
	.non_maskable_interrupt = reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt),
	.hard_fault             = reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt),
	.mem_manage             = reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt),
	.bus_fault              = reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt),
	.usage_fault            = reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt),
	.supervisor_call        = reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt),
	.debug_monitor          = reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt),
	.async_supervisor_call  = reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt),
	.systick                = reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt),
	.external               = {reinterpret_cast<arm::v7::nvic::function_t>(&arm::v7::nvic::default_interrupt)},
};
void* arm::v7::nvic::interrupt_vector_table_ptr = reinterpret_cast<void*>(&arm::v7::nvic::interrupt_vector_table);

namespace dcd = nxp::imxrt1060::device_configuration_data;

struct [[gnu::packed, gnu::aligned(1)]] dcd_t {
	const dcd::data_t header = {
		.header =
			{
				.length = sizeof(dcd_t),
			},
	};
	const dcd::write_t gpr1 = {
		.header =
			{
				.parameter =
					{
						.width = dcd::width::LONG,
						.set   = true,
						.mask  = true,
					},
			},
		.address = const_cast<intptr_t*>(&__IMXRT1060_IOMUXC_GPR1),
		.value_or_mask =
			{
				.number = size_t(1) << size_t(31),
			},
	};
	const dcd::write_t gpr2 = {
		.header =
			{
				.parameter =
					{
						.width = dcd::width::LONG,
						.set   = true,
						.mask  = true,
					},
			},
		.address = const_cast<intptr_t*>(&__IMXRT1060_IOMUXC_GPR2),
		.value_or_mask =
			{
				.number = (1 << 14 /* Memory Deep Sleep Enabled */) | (1 << 12 /* L2 Power Saving Enabled */),
			},
	};
	const dcd::write_t gpr3 = {
		.header =
			{
				.parameter =
					{
						.width = dcd::width::LONG,
						.set   = false,
						.mask  = true,
					},
			},
		.address = const_cast<intptr_t*>(&__IMXRT1060_IOMUXC_GPR3),
		.value_or_mask =
			{
				.number = 0b111100001111 /* Turn off 1 cycle delay for AXI based memory read/write. */,
			},
	};
	const dcd::write_t gpr17 = {
		.header =
			{
				.parameter =
					{
						.width = dcd::width::LONG,
						.set   = true,
						.mask  = false,
					},
			},
		.address = const_cast<intptr_t*>(&__IMXRT1060_IOMUXC_GPR17),
		.value_or_mask =
			{
				.number = (size_t)(&__flexram_bank_config),
			},
	};
	const dcd::write_t gpr16 = {
		.header =
			{
				.parameter =
					{
						.width = dcd::width::LONG,
						.set   = true,
						.mask  = true,
					},
			},
		.address = const_cast<intptr_t*>(&__IMXRT1060_IOMUXC_GPR16),
		.value_or_mask =
			{
				// C/C++ is unable to know this at compile time, as it is only placed into the right place at link time.
				.number = /*(reinterpret_cast<size_t>(&__interrupt_vector_table) & ~0x7F) |*/ (1 << 2) | (0b11 /* Default from Documentation */),
			},
	};
};

extern "C" [[gnu::used, gnu::section(".dcd")]] const dcd_t __dcd = {};

extern "C" [[gnu::used, gnu::section(".imageVectorTable")]] const nxp::imxrt1060::image_vector_table_t __image_vector_table = {
#if NXP_IVT == 0x43
	.entryPoint = &__main,
#else
	.entryPoint = &arm::v7::nvic::interrupt_vector_table,
#endif
	// ToDo: Use DCD to set up FlexRAM and similar static GPR stuff.
	.dcd      = reinterpret_cast<decltype(nxp::imxrt1060::image_vector_table_t::dcd)>(&__dcd),
	.bootData = &__boot_data,
	.self     = &__image_vector_table,
};
