#include <arm/cm7/nvic.hpp>
#include <chip.h>
#include <nxp/imxrt1060/bootdata.hpp>
#include <nxp/imxrt1060/imagevectortable.hpp>
#include <nxp/kinetis.hpp>
#include "board.h"

extern "C" void __main(void);

[[gnu::used, gnu::section(".flashLoader")]] const nxp::kinetis_t __flash_loader = {
	.sflashA1Size = BOARD_FLASH_SIZE,
};

[[gnu::used, gnu::section(".bootData")]] const nxp::imxrt1060::boot_data_t __boot_data = {
	.start  = reinterpret_cast<decltype(nxp::imxrt1060::boot_data_t::start)>(BOARD_FLASH_START),
	.length = reinterpret_cast<decltype(nxp::imxrt1060::boot_data_t::length)>(BOARD_FLASH_USED),
	.plugin = 0,
};

[[gnu::used,
  gnu::section(".interruptVectorTable")]] arm::cm7::nvic::interrupt_vector_table_t __interrupt_vector_table = {
	.initial_stack_pointer = reinterpret_cast<const void*>(&__stack_start),
	/* This should be zero according to the documentation, but if its zero we just crash. Very strange behavior
	   ¯\_(ツ)_/¯. */
	.reset = reinterpret_cast<void (*)()>(&__main),
};
void* __interrupt_vector_table_ptr = reinterpret_cast<void*>(&__interrupt_vector_table);

[[gnu::used, gnu::section(".imageVectorTable")]] const nxp::imxrt1060::image_vector_table_t __image_vector_table = {
#if NXP_IVT == 0x43
	.entryPoint = &__main,
#else
	.ivt = &__interrupt_vector_table,
#endif
	.dcd      = nullptr, // reinterpret_cast<decltype(nxp::imxrt1060::image_vector_table_t::dcd)>(&__dcd),
	.bootData = &__boot_data,
	.self     = &__image_vector_table,
};
