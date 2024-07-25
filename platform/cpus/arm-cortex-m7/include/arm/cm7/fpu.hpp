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

#pragma once
#include <cinttypes>
#include <cstddef>

namespace arm::cm7::fpu {
	/** Does this hardware support an FPU?
	 */
	bool supported() noexcept;

	/** Is the FPU currently enabled?
	 */
	bool enabled() noexcept;

	/** Enable the installed Floating Point Unit.
	 *
	 * Attempting to use hard-floats without an enabled FPU will cause crashes.
	 */
	bool enable() noexcept;

	/** Disable access to the Floating Point Unit.
	 *
	 * Ensure all code after this point uses soft-float.
	 */
	void disable() noexcept;
} // namespace arm::cm7::fpu
