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

template<std::size_t address>
struct registerUndefined {
	private:
	static volatile inline std::size_t& ref = *reinterpret_cast<volatile std::size_t*>(address);

	protected:
	[[gnu::always_inline]]
	registerUndefined&
		operator=(std::size_t value)
	{
		ref = value;
		return *this;
	}

	[[gnu::always_inline]]
	registerUndefined&
		operator|=(std::size_t value)
	{
		ref |= value;
		return *this;
	}

	[[gnu::always_inline]] operator std::size_t() const
	{
		return ref;
	}
};

template<std::size_t address>
struct registerReadWrite : registerUndefined<address> {
	public:
	template<typename T>
	[[gnu::always_inline]] operator T() const
	{
		return registerUndefined<address>::operator T();
	}

	[[gnu::always_inline]] operator std::size_t() const
	{
		return registerUndefined<address>::operator std::size_t();
	}

	template<typename T>
	[[gnu::always_inline]]
	registerReadWrite&
		operator=(T value)
	{
		return static_cast<registerReadWrite&>(registerUndefined<address>::operator=(value));
	}

	[[gnu::always_inline]]
	registerReadWrite&
		operator=(std::size_t value)
	{
		return static_cast<registerReadWrite&>(registerUndefined<address>::operator=(value));
	}

	template<typename T>
	[[gnu::always_inline]]
	registerReadWrite&
		operator|=(T value)
	{
		return static_cast<registerReadWrite&>(registerUndefined<address>::operator|=(value));
	}

	[[gnu::always_inline]]
	registerReadWrite&
		operator|=(std::size_t value)
	{
		return static_cast<registerReadWrite&>(registerUndefined<address>::operator|=(value));
	}
};

template<std::size_t address>
struct registerReadOnly : registerUndefined<address> {
	public:
	registerReadOnly& operator=(std::size_t value) = delete;

	template<typename T>
	[[gnu::always_inline]] operator T() const
	{
		return registerUndefined<address>::operator T();
	}

	[[gnu::always_inline]] operator std::size_t() const
	{
		return registerUndefined<address>::operator size_t();
	}
};

template<std::size_t address>
struct registerWriteOnly : registerUndefined<address> {
	public:
	template<typename T>
	[[gnu::always_inline]]
	registerWriteOnly&
		operator=(T value)
	{
		return static_cast<registerWriteOnly&>(registerUndefined<address>::operator=(value));
	}

	[[gnu::always_inline]]
	registerWriteOnly&
		operator=(std::size_t value)
	{
		return static_cast<registerWriteOnly&>(registerUndefined<address>::operator=(value));
	}

	template<typename T>
	[[gnu::always_inline]]
	registerWriteOnly&
		operator|=(T value)
	{
		return static_cast<registerWriteOnly&>(registerUndefined<address>::operator|=(value));
	}

	[[gnu::always_inline]]
	registerWriteOnly&
		operator|=(std::size_t value)
	{
		return static_cast<registerWriteOnly&>(registerUndefined<address>::operator|=(value));
	}
};
