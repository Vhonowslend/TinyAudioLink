#include "arm/v7/systick.hpp"
#include "arm/v7/v7.hpp"

bool arm::v7::systick::supports_external_clock()
{
	size_t calib = arm::v7::SYST_CALIB;
	return (calib & size_t(0b1 << 31)) == 0;
}

bool arm::v7::systick::calibrated(size_t& ten_milliseconds)
{
	size_t calib     = arm::v7::SYST_CALIB;
	bool   accurate  = (calib & size_t(0b1 << 30)) == 0;
	ten_milliseconds = calib & ((1 << 24) - 1);
	return accurate;
}

size_t arm::v7::systick::reset_value()
{
	return arm::v7::SYST_RVR;
}

void arm::v7::systick::reset_value(size_t value)
{
	arm::v7::SYST_RVR = value;
}

size_t arm::v7::systick::value()
{
	return arm::v7::SYST_CVR;
}

void arm::v7::systick::value(size_t value)
{
	arm::v7::SYST_CVR = value;
}

bool arm::v7::systick::enabled()
{
	size_t csr = arm::v7::SYST_CSR;
	return (csr & size_t(0b1)) != 0;
}

bool arm::v7::systick::interrupt_enabled()
{
	size_t csr = arm::v7::SYST_CSR;
	return (csr & size_t(0b1 << 1)) != 0;
}

void arm::v7::systick::control(bool enable, bool interrupt, arm::v7::systick::clock_source source)
{
	size_t csr        = arm::v7::SYST_CSR; // Mask out the area we overwrite.
	csr               = (csr & ((1 << 3) - 1)) | ((source == clock_source::INTERNAL ? 1 : 0) << 2) | ((interrupt ? 1 : 0) << 1) | ((enable ? 1 : 0) << 0);
	arm::v7::SYST_CSR = csr;
}
