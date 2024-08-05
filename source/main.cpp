// TinyAudioLink - Seamlessly transfer Audio between USB capable devices
// Copyright (C) 2019 Michael Fabian 'Xaymar' Dirks
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <arm/v7/nvic.hpp>
#include <arm/v7/systick.hpp>
#include <arm/v7/v7.hpp>
#include <atomic.hpp>
#include <cinttypes>
#include <cstddef>
#include <nxp/imxrt1060/gpio.hpp>
#include <nxp/imxrt1060/imxrt1060.hpp>

using namespace nxp;

static size_t counter = 0;

[[gnu::interrupt, gnu::used]]
void _int_systick() noexcept
{
	nxp::imxrt1060::GPIO2.direction = 0b1000;
	nxp::imxrt1060::GPIO2.toggle    = 0b1000;
	counter++;
}

extern "C" [[gnu::used]]
int main() noexcept
{
	nxp::imxrt1060::GPIO2.direction = 0b1000;

	size_t ten_milliseconds;
	{ // Enable SysTick timer support.
		arm::v7::nvic::critical_section cs;

		// Enable SysTick intterupt.
		for (size_t idx = 0, edx = arm::v7::ICTR.operator size_t() + static_cast<size_t>(arm::v7::nvic::identifier_t::EXTERNAL); idx < edx; ++idx) {
			arm::v7::nvic::enable(static_cast<arm::v7::nvic::identifier_t>(idx), arm::v7::nvic::priority_t::NORMAL, &_int_systick);
		}
		arm::v7::nvic::enable(arm::v7::nvic::identifier_t::SYSTEM_TIMER_TICK, arm::v7::nvic::priority_t::NORMAL, &_int_systick);

		bool calibrated = arm::v7::systick::calibrated(ten_milliseconds);
		if (calibrated && (ten_milliseconds > 0)) {
			arm::v7::systick::reset_value(ten_milliseconds * 10); // Internal Clock appears to be 1mHz.
			arm::v7::systick::control(true, true, arm::v7::systick::clock_source::INTERNAL);
		} else {
			arm::v7::systick::reset_value(100000 - 1); // External Clock appears to be 100kHz.
			arm::v7::systick::control(true, true, arm::v7::systick::clock_source::EXTERNAL);
		}
	}

	size_t stackpointer;
	asm volatile("mov %[out], sp" : [out] "=r"(stackpointer)::);

	nxp::imxrt1060::GPIO2.data = 0b1000;

	uint8_t idx  = 0;
	bool    last = false;
	while (true) {
		// On (for ~10ms)
		/*nxp::imxrt1060::GPIO2.data = 0b1000;
		for (size_t i = 0; i < 600000 * 5; i = i + 1) {*/
		asm volatile("nop");
		//}

		/*// Off (for ~10ms)
		nxp::imxrt1060::GPIO2.data = 0x0;
		for (size_t i = 0; i < 600000 * 5; i = i + 1) {
			asm volatile("nop");
		}

		// On (for ~10ms)
		nxp::imxrt1060::GPIO2.data = 0b1000;
		for (size_t i = 0; i < 600000 * 5; i = i + 1) {
			asm volatile("nop");
		}

		// Value (for ~980ms)
		bool set                   = (arm::v7::systick::value() >> idx) & 1;
		nxp::imxrt1060::GPIO2.data = set ? 0b1000 : 0;
		for (size_t i = 0; i < 600000 * 10; i = i + 1) {
			asm volatile("nop");
		}

		idx = (idx + 1) % 32;
		if (idx == 0) {
			nxp::imxrt1060::GPIO2.data = 0b1000;
			for (size_t i = 0; i < 600000 * 300; i = i + 1) {
				asm volatile("nop");
			}
		}*/
	}

	while (true) {
		arm::v7::wait_for_interrupt();
	}

	return 0;
}
