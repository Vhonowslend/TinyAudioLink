#pragma once
#import "cinttypes"
#import "cstddef"

namespace arm::v7::systick {
	enum class clock_source : uint8_t {
		/** Use the external clock.
		 *
		 * Due to the way ARM has designed these CPUs, the internal clock is tied to the processor frequency,
		 * thus making them extremely inaccurate in over-/underclocking, sleep states, and similar behavior.
		 * The accuracy of this timer depends on the SoC, however it appears to be limited to the same maximum
		 * accuracy as the internal clock.
		 */
		EXTERNAL = 0,

		/** Use the internal clock.
		 *
		 * The internal clock is susceptible to drift from over- & underclocking, entering/leaving sleep,
		 * spending too much time in interrupts, etc. The actual frequency of the timer is unclear, and
		 * appears to vary from cpu to cpu, though usually appears to be a 10mHz clock.
		 */
		INTERNAL = 1,
	};

	/** Is an external reference clock supported?
	 */
	[[gnu::always_inline]]
	bool supports_external_clock() noexcept;

	[[gnu::always_inline]]
	bool calibrated(size_t& ten_milliseconds) noexcept;

	[[gnu::always_inline]]
	size_t reset_value() noexcept;

	[[gnu::always_inline]]
	void reset_value(size_t value) noexcept;

	[[gnu::always_inline]]
	size_t value() noexcept;

	[[gnu::always_inline]]
	void value(size_t value) noexcept;

	[[gnu::always_inline]]
	bool enabled() noexcept;

	[[gnu::always_inline]]
	bool interrupt_enabled() noexcept;

	[[gnu::always_inline]]
	void control(bool enable, bool interrupt, clock_source source) noexcept;
} // namespace arm::v7::systick
