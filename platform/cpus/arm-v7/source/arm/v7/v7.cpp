#include "arm/v7/v7.hpp"

[[gnu::naked]]
void arm::v7::instruction_synchronization_barrier() noexcept
{
	__asm volatile("isb");
}

[[gnu::naked]]
void arm::v7::data_synchronization_barrier() noexcept
{
	__asm volatile("dsb");
}

[[gnu::naked]]
void arm::v7::memory_synchronization_barrier() noexcept
{
	__asm volatile("dmb");
}

void arm::v7::supervisor_call(uint8_t id) noexcept
{
	__asm volatile("svc %[id]" : : [id] "ri"(id));
}

[[gnu::naked]]
void arm::v7::signal_event() noexcept
{
	__asm volatile("sev");
}

[[gnu::naked]]
void arm::v7::wait_for_event() noexcept
{
	__asm volatile("wfe");
}

[[gnu::naked]]
void arm::v7::wait_for_interrupt() noexcept
{
	__asm volatile("wfi");
}
