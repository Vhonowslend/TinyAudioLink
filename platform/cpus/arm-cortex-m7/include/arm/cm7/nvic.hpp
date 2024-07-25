#pragma once
#include <cinttypes>
#include <cstddef>
#include <register.hpp>

namespace arm::cm7::nvic {
	typedef void (*function_t)(void);

	enum class identifier_t : uint32_t {
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
		EXTERNAL_MAX            = 495,
	};

	enum class priority_t : uint8_t {
		IMMEDIATE = 0b00000000,
		HIGH      = 0b01000000,
		NORMAL    = 0b10000000,
		LOW       = 0b11000000,
		IDLE      = 0b11111111,
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
			function_t interrupts[495] = {0};

			[[gnu::packed, gnu::aligned(1)]] struct {
				function_t reset;
				function_t non_maskable_interrupt;
				function_t hard_fault;
				function_t mem_manage;
				function_t bus_fault;
				function_t usage_fault;
				function_t __reserved0[3];
				function_t supervisor_call;
				function_t debug_monitor;
				function_t __reserved1;
				function_t async_supervisor_call;
				function_t systick;
				function_t external[480];
			};
		};
	};

	static_assert(sizeof(interrupt_vector_table_t) == (496 * 4), "Interrupt Vector Table size mismatch!");
} // namespace arm::cm7::nvic
