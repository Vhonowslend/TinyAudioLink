#pragma once
#include <cinttypes>
#include <cstddef>
#include <register.hpp>
#include "arm/v7/v7.hpp"

namespace arm::v7::nvic {
	typedef void (*function_t)(void);

	/** Interrupt Vector Table
	 * - Must be aligned to the nearest larger power of two boundary larger than itself.
	 * - At boot, all entries except initial_stack_pointer MUST be zero, or the CPU will crash.
	 * - If an interrupt is still set to 0, but is triggered, then a usage_fault is triggered.
	 *   - If this happens before usage_fault is enable, a hard_fault is triggered.
	 */
	struct [[gnu::packed, gnu::aligned(1)]] interrupt_vector_table_t {
		union {
			[[gnu::packed, gnu::aligned(1)]] struct {
				const void* initial_stack_pointer; // Id 0, not used beyond reboot.

				// Exceptions
				function_t reset; // Id 1
				function_t non_maskable_interrupt; // Id 2
				function_t hard_fault; // Id 3
				function_t mem_manage; // Id 4
				function_t bus_fault; // Id 5
				function_t usage_fault; // Id 6
				function_t __reserved0[4]; // Id 7, 8, 9, 10
				function_t supervisor_call; // Id 11
				function_t debug_monitor; // Id 12
				function_t __reserved1; // Id 13

				// Interrupts
				function_t async_supervisor_call; // Id 14
				function_t systick; // Id 15?!
				function_t external[480]; // 16..496
			};

			function_t interrupts[496] = {0};
		};
	};

	static_assert(sizeof(interrupt_vector_table_t) == (496 * 4), "Interrupt Vector Table size mismatch!");

	extern "C" interrupt_vector_table_t interrupt_vector_table;
	extern "C" void*                    interrupt_vector_table_ptr;

	enum class identifier_t : size_t {
		RESET                   = 1,
		NON_MASKABLE_INTERRUPT  = 2,
		NMI                     = 2,
		HARD_FAULT              = 3,
		MEM_MANAGE              = 4,
		BUS_FAULT               = 4,
		USAGE_FAULT             = 5,
		SUPERVISOR_CALL         = 11,
		SVCALL                  = 11,
		DEBUG_MONITOR           = 12,
		ASYNC_SUPERVISOR_CALL   = 14,
		PENDING_SUPERVISOR_CALL = 14,
		PENDSV                  = 14,
		SYSTEM_TIMER_TICK       = 15,
		SYSTICK                 = 15,
		EXTERNAL                = 16,
		USER                    = 16,
		EXTERNAL_MAX            = 496,
		USER_MAX                = 496,
	};

	enum class priority_t : uint8_t {
		REALTIME = 0b0011'1111,
		HIGH     = 0b0111'1111,
		NORMAL   = 0b1011'1111,
		LOW      = 0b1101'1111,
		IDLE     = 0b1111'1111,
	};

	[[gnu::always_inline]]
	void enable(identifier_t id, priority_t priority, function_t handler);

	[[gnu::always_inline]]
	void disable(identifier_t id);

	/** Critical Section
	 *
	 * Disable all interrupt handling, except for those with negative or no priority.
	 */
	class critical_section {
		bool    _old_primask;
		bool    _old_faultmask;
		uint8_t _old_basepri;

	public:
		[[gnu::always_inline]] ~critical_section();

		[[gnu::always_inline]] critical_section();
	};
} // namespace arm::v7::nvic
