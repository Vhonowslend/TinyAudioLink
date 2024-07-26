#include "arm/v7/nvic.hpp"

extern "C" void   __main(void);
extern "C" size_t __stack_start;

[[gnu::used,
  gnu::section(
	  ".interruptVectorTable")]] arm::v7::nvic::interrupt_vector_table_t arm::v7::nvic::interrupt_vector_table = {
	.initial_stack_pointer = reinterpret_cast<const void*>(&__stack_start),
	// When using a IVT version <=4.2, the entry point is the reset interrupt, contrary to the ARM
	// documentation for this. This must be zeroed out for all other versions, but seems to do
	// nothing if it's not set to zero, as there is no way to trigger a software reset anyway.
	//
	// Additionally, __main is responsible for resetting the state of the SoC anyway, so this does
	// what we want at all times.
	.reset = reinterpret_cast<void (*)()>(&__main),
};
void* arm::v7::nvic::interrupt_vector_table_ptr = reinterpret_cast<void*>(&arm::v7::nvic::interrupt_vector_table);
