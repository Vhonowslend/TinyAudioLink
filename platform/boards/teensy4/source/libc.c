#include <arm/cm7/cm7.h>
#include <nxp/imxrt1060/imxrt1060.h>

[[gnu::section(".flashCode")]]
void _exit(int code)
{
	// Wait for memory to sychronize entirely.
	asm volatile("isb;dsb;dmb" ::: "memory");

	// Enable debug, and request a local reset.
	asm volatile(
		"str %[dhcsr_val], %[dhcsr];"
		"str %[aircr_val], %[aircr]"
		: [dhcsr] "=g"(__CORTEXM7_DHCSR), [aircr] "=g"(__CORTEXM7_AIRCR)
		: [dhcsr_val] "r"(0xA05F0001), [aircr_val] "r"(0b101)
		:);

	// Now just loop until it happens, we can't affect this anyway.
	asm volatile("b 0" :::);

	__builtin_unreachable();
}

// This is just fucked up, but hey, can't do anything because libc++ AND libUnwind link against the FILE* handle. Which as you might guess, is useless.
[[gnu::used]] void* stderr = 0;
