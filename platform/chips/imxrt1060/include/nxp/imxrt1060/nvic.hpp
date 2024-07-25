#pragma once
#include <cinttypes>
#include <cstddef>

namespace nxp::imxrt1060::nvic {
	typedef void (*interrupt_function_t)();

	enum class interrupt_t : uint32_t {
		RESET                  = 1,
		NON_MASKABLE_INTERRUPT = 2,
		HARD_FAULT             = 3,
		MEM_MANAGE             = 4,
		BUS_FAULT              = 4,
		USAGE_FAULT            = 5,
		SERVICE_CALL           = 11,
		DEBUG_MONITOR          = 12,
		ASYNC_SERVICE_CALL     = 14,
		PENDING_SERVICE_CALL   = 14,
		SYSTICK                = 15,
		EXTERNAL               = 16,
		EXTERNAL_MAX           = 241,
	};

	struct [[gnu::packed, gnu::aligned(1)]] interrupt_vector_table_t {
		const void* initial_stack_pointer;
		union {
			interrupt_function_t interrupts[241] = {0};
			[[gnu::packed, gnu::aligned(1)]] struct {
				interrupt_function_t reset;
				interrupt_function_t non_maskable_interrupt;
				interrupt_function_t hard_fault;
				interrupt_function_t mem_manage;
				interrupt_function_t bus_fault;
				interrupt_function_t usage_fault;
				interrupt_function_t __reserved0[3];
				interrupt_function_t svcall;
				interrupt_function_t debug_monitor;
				interrupt_function_t __reserved1;
				interrupt_function_t pendsv;
				interrupt_function_t systick;
				interrupt_function_t external[227];
			} named;
		};
	};
	static_assert(sizeof(interrupt_vector_table_t) == 968, "Interrupt Vector Table must be 968 bytes long.");
} // namespace nxp::imxrt1060::nvic
