#include "arm/v7/nvic.hpp"
#include "arm/v7/v7.hpp"
#import "cinttypes"
#import "cstddef"

[[gnu::interrupt, gnu::used]]
void arm::v7::nvic::default_interrupt() noexcept
{}

void arm::v7::nvic::initialize() noexcept
{
	for (size_t idx = 0, edx = arm::v7::ICTR; idx < edx; ++idx) {
		arm::v7::nvic::interrupt_vector_table.interrupts[idx] = &default_interrupt;
	}
}

void arm::v7::nvic::enable(arm::v7::nvic::identifier_t id, arm::v7::nvic::priority_t priority, arm::v7::nvic::function_t fn) noexcept
{
	size_t idx = static_cast<size_t>(id);

	// Don't allow this to be interrupted, it's bad for us.
	arm::v7::nvic::critical_section cs;

	// Set Handler
	arm::v7::nvic::interrupt_vector_table.interrupts[idx] = fn;

	if (idx < 4) {
		// Stack, Reset, NMI and HardFault are non-configurable and non-maskable.
	} else if (idx < 16) {
		// System Interrupt 4 to 15, configurable, but non-maskable
		size_t idx = idx - 4;

		// Set Priority
		volatile std::size_t*    rp = (&arm::v7::SHPR1.ref) + (idx / 4);
		arm::v7::nvic_priority_t vp{
			.value = static_cast<size_t>(*rp),
		};
		vp.priority[static_cast<size_t>(id) % 4] = static_cast<uint8_t>(priority);
		*rp                                      = vp.value;

	} else {
		// User Interrupts start at 16, but our registers start at 0.
		size_t idx = idx - 16; // Offset by 16.

		// Set Priority
		volatile std::size_t*    rp = (&arm::v7::NVIC_IPR0.ref) + (idx / 4);
		arm::v7::nvic_priority_t vp{
			.value = static_cast<size_t>(*rp),
		};
		vp.priority[static_cast<size_t>(id) % 4] = static_cast<uint8_t>(priority);
		*rp                                      = vp.value;
	}

	// Enable Interrupt
	volatile std::size_t* rs = (&arm::v7::NVIC_ISER0.ref) + (idx / 32);
	*rs                      = size_t(1) << (idx % 32); // Only accepts 1, 0s are ignored.
}

void arm::v7::nvic::disable(arm::v7::nvic::identifier_t id) noexcept
{
	size_t idx = static_cast<size_t>(id);

	// Don't allow this to be interrupted, it's bad for us.
	arm::v7::nvic::critical_section cs;

	// Clear Handler
	arm::v7::nvic::interrupt_vector_table.interrupts[idx] = nullptr;

	if (idx < 4) {
		// Stack, Reset, NMI and HardFault are non-configurable and non-maskable.
	} else if (idx < 16) {
		// System Interrupt 4 to 15
		size_t idx = idx - 4;

		// Set Priority
		volatile std::size_t*    rp = (&arm::v7::SHPR1.ref) + (idx / 4);
		arm::v7::nvic_priority_t vp{
			.value = static_cast<size_t>(*rp),
		};
		vp.priority[static_cast<size_t>(id) % 4] = 0;
		*rp                                      = vp.value;
	} else {
		// User Interrupts start at 16, but our registers start at 0.
		size_t idx = idx - 16; // Offset by 16.

		// Clear Priority
		volatile std::size_t*    rp = (&arm::v7::NVIC_IPR0.ref) + (idx / 4);
		arm::v7::nvic_priority_t vp{
			.value = static_cast<size_t>(*rp),
		};
		vp.priority[static_cast<size_t>(id) % 4] = 0;
		*rp                                      = vp.value;
	}

	// Disable Interrupt
	volatile std::size_t* rs = (&arm::v7::NVIC_ICER0.ref) + (static_cast<intptr_t>(id) / 32);
	*rs                      = size_t(1) << (idx % 32); // Only accepts 1, 0s are ignored.
}

arm::v7::nvic::critical_section::~critical_section() noexcept
{
	asm volatile("msr primask, %[v]" : : [v] "r"(_old_primask));
	asm volatile("msr faultmask, %[v]" : : [v] "r"(_old_faultmask));
	asm volatile("msr basepri, %[v]" : : [v] "r"(_old_basepri));
}

arm::v7::nvic::critical_section::critical_section() noexcept
{
	asm volatile("mrs %[v], primask" : [v] "=r"(_old_primask));
	asm volatile("msr primask, %[v]" : : [v] "r"(1));

	asm volatile("mrs %[v], basepri" : [v] "=r"(_old_basepri));
	asm volatile("msr basepri, %[v]" : : [v] "r"(0xFF));

	asm volatile("mrs %[v], faultmask" : [v] "=r"(_old_faultmask));
	asm volatile("msr faultmask, %[v]" : : [v] "r"(1));
}
