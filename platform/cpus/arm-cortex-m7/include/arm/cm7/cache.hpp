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

namespace arm::cm7::cache {
	namespace data {
		/** Is the cache enabled?
		 */
		bool enabled();

		/** Invalidate the cache.
		 */
		void invalidate();

		/** Clean the cache
		 */
		void clean();

		/** Clean and invalidate the cache
		 */
		void clean_invalidate();

		/** Flush the cache
		 * 
		 */
		void flush();

		/** Enable the cache.
		 * 
		 * This will automatically call clean_invalidate().
		 */
		void enable();

		/** Disable the cache.
		 * 
		 * This will automatically call flush().
		 */
		void disable();
	} // namespace data

	namespace instruction {
		/** Is the cache enabled?
		 */
		bool enabled();

		/** Invalidate the cache.
		 */
		void invalidate();

		/** Enable the cache.
		 * Remember to invalidate the cache first.
		 */
		void enable();

		/** Disable the cache.
		 */
		void disable();
	} // namespace instruction
} // namespace arm::cm7::cache
