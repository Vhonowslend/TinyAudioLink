#pragma once
#include <cinttypes>
#include <cstddef>

namespace arm::cm7::nvic {
	typedef void (*interrupt_function_t)();

	enum class interrupt_t : uint32_t {
		RESET                   = 1,
		NON_MASKABLE_INTERRUPT  = 2,
		HARD_FAULT              = 3,
		MEM_MANAGE              = 4,
		BUS_FAULT               = 4,
		USAGE_FAULT             = 5,
		SUPERVISOR_CALL         = 11,
		DEBUG_MONITOR           = 12,
		ASYNC_SUPERVISOR_CALL   = 14,
		PENDING_SUPERVISOR_CALL = 14,
		SYSTICK                 = 15,
		EXTERNAL                = 16,
		EXTERNAL_MAX            = 241,
	};

	/** Interrupt Vector Table
	 * - Must be aligned to the nearest larger power of two boundary larger than itself.
	 * - At boot, all entries except initial_stack_pointer MUST be zero, or the CPU will crash.
	 * - If an interrupt is still set to 0, but is triggered, then a usage_fault is triggered.
	 *   - If this happens before usage_fault is enable, a hard_fault is triggered.
 	 */
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
				interrupt_function_t supervisor_call;
				interrupt_function_t debug_monitor;
				interrupt_function_t __reserved1;
				interrupt_function_t async_supervisor_call;
				interrupt_function_t systick;
				interrupt_function_t external[227];
			};
		};
	};
	static_assert(sizeof(interrupt_vector_table_t) == 968, "Interrupt Vector Table must be 968 bytes long.");
} // namespace arm::cm7::nvic
