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

namespace arm::v7::cache {
	namespace data {
		/** Is the cache enabled?
		 */
		[[gnu::always_inline]]
		bool enabled() noexcept;

		/** Invalidate the cache.
		 */
		[[gnu::always_inline]]
		void invalidate() noexcept;

		/** Clean the cache
		 */
		[[gnu::always_inline]]
		void clean() noexcept;

		/** Clean and invalidate the cache
		 */
		[[gnu::always_inline]]
		void clean_invalidate() noexcept;

		/** Flush the cache
		 */
		[[gnu::always_inline]]
		void flush() noexcept;

		/** Enable the cache.
		 *
		 * This will automatically call clean_invalidate().
		 */
		[[gnu::always_inline]]
		void enable() noexcept;

		/** Disable the cache.
		 *
		 * This will automatically call flush().
		 */
		[[gnu::always_inline]]
		void disable() noexcept;
	} // namespace data

	namespace instruction {
		/** Is the cache enabled?
		 */
		[[gnu::always_inline]]
		bool enabled() noexcept;

		/** Invalidate the cache.
		 */
		[[gnu::always_inline]]
		void invalidate() noexcept;

		/** Enable the cache.
		 * Remember to invalidate the cache first.
		 */
		[[gnu::always_inline]]
		void enable() noexcept;

		/** Disable the cache.
		 */
		[[gnu::always_inline]]
		void disable() noexcept;
	} // namespace instruction
} // namespace arm::v7::cache
