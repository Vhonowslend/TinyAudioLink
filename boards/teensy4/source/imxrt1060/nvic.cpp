#include "imxrt1060/nvic.hpp"
#include <cinttypes>
#include <cstddef>
#include "arm/cm7.hpp"
#include "bootloader.hpp"
#include "imxrt1060/iomuxc.hpp"

extern std::size_t __stack_start;

[[gnu::used, gnu::section(".interruptVectorTable")]] imxrt1060::nvic::interrupt_vector_table_t imxrt1060::nvic::__interrupt_vector_table = {
	.initialStackPointer = &__stack_start,
	.reset               = &_start,
};

void imxrt1060::nvic::initialize()
{
	// Set Interrupt Vector Offset Register (VTOR)
	imxrt1060::iomuxc::gpr::GPR16 |= (size_t)&nvic::__interrupt_vector_table;
	arm::cm7::VTOR = (size_t)&__interrupt_vector_table;
}
