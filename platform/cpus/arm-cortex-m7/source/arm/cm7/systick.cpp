#include "arm/cm7/systick.hpp"
#include "arm/cm7/cm7.hpp"

static size_t arm7_cm7_systick_ticks  = 0;
static size_t arm7_cm7_systick_cycles = 0;

void arm::cm7::systick::initialize()
{
	extern size_t __external_clock_speed;

	// Disable and reset the SysTick clock (handle soft-reset state).
	arm::cm7::SYST_CSR = 0;
	arm::cm7::SYST_CVR = 0;

	// Check if there is an external clock to fall back to, and if the internal clock is still calibrated.
	size_t   systick      = arm::cm7::SYST_CALIB;
	bool     is_skewed    = (systick & size_t(0b1 << 30)) == 1;
	bool     has_external = (systick & size_t(0b1 << 31)) == 0;
	uint32_t tenms        = (systick & ((1 << 24) - 1));

	// Is the internal clock calibrated and safe to use?
	if ((!is_skewed) && (tenms > 0)) {
		// Then use it, as it is faster and has higher accuracy.

	} else if (has_external) {
		// Otherwise fall back to the external clock, which may need to be manually calibrated first.
	}
}

/*
static uint64_t tick      = 0;
static uint64_t cycle10ms = 0;

extern "C" [[gnu::used]]
static void int_systick(void)
{
	++tick;
};
	{ // Enable SysTick clock

		// Do we have a reference clock?
		if ((systick & size_t(0b1 << 31)) == 0) {
			// Yes, so attempt to use it.
			bool is_10ms_skewed = (systick & size_t(1 << 30)) != 0;
			if (!is_10ms_skewed) {
				cycle10ms = systick & ((1 << 24) - 1);
				arm::cm7::SYST_CSR |= 0b100;
			} else {
				// Clock speed is different, so the calibration value is skewed.
				// We'll have to fall back to external clock sources.
				arm::cm7::SYST_CSR &= ~0b100;
			}
		}

		// Were we able to use the reference clock without issues?
		if (cycle10ms == 0) {
			// No, so we need to use the external
		}
	}

	arm::cm7::SYST_CVR = size_t(0);
	arm::cm7::SYST_RVR = size_t(cycle10ms / 1000);
	arm::cm7::SYST_CSR = size_t(0b011);

	arm::cm7::SHPR3 = 0x20200000;
*/
