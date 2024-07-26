#include "arm/v7/v7.hpp"

[[gnu::naked]]
void arm::v7::instruction_synchronization_barrier()
{
	__asm volatile("isb");
}

[[gnu::naked]]
void arm::v7::data_synchronization_barrier()
{
	__asm volatile("dsb");
}

[[gnu::naked]]
void arm::v7::memory_synchronization_barrier()
{
	__asm volatile("dmb");
}

void arm::v7::supervisor_call(uint8_t id)
{
	__asm volatile("svc %[id]" : : [id] "ri"(id));
}

[[gnu::naked]]
void arm::v7::signal_event()
{
	__asm volatile("sev");
}

[[gnu::naked]]
void arm::v7::wait_for_event()
{
	__asm volatile("wfe");
}

[[gnu::naked]]
void arm::v7::wait_for_interrupt()
{
	__asm volatile("wfi");
}
