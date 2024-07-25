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

template<std::uintptr_t address>
struct register_unknown {
public:
	static volatile inline std::uintptr_t& ref = *reinterpret_cast<std::uintptr_t*>(address);

protected:
	[[gnu::always_inline]]
	register_unknown&
		operator=(std::size_t value)
	{
		ref = value;
		return *this;
	}

	[[gnu::always_inline]]
	register_unknown&
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

template<std::uintptr_t address>
struct register_read_write : public register_unknown<address> {
public:
	template<typename T>
	[[gnu::always_inline]] operator T() const
	{
		return register_unknown<address>::operator T();
	}

	[[gnu::always_inline]] operator std::size_t() const
	{
		return register_unknown<address>::operator std::size_t();
	}

	template<typename T>
	[[gnu::always_inline]]
	register_read_write&
		operator=(T value)
	{
		return static_cast<register_read_write&>(register_unknown<address>::operator=(value));
	}

	[[gnu::always_inline]]
	register_read_write&
		operator=(std::size_t value)
	{
		return static_cast<register_read_write&>(register_unknown<address>::operator=(value));
	}

	template<typename T>
	[[gnu::always_inline]]
	register_read_write&
		operator|=(T value)
	{
		return static_cast<register_read_write&>(register_unknown<address>::operator|=(value));
	}

	[[gnu::always_inline]]
	register_read_write&
		operator|=(std::size_t value)
	{
		return static_cast<register_read_write&>(register_unknown<address>::operator|=(value));
	}
};

template<std::uintptr_t address>
struct register_read : public register_unknown<address> {
public:
	register_read& operator=(std::size_t value) = delete;

	template<typename T>
	[[gnu::always_inline]] operator T() const
	{
		return register_unknown<address>::operator T();
	}

	[[gnu::always_inline]] operator std::size_t() const
	{
		return register_unknown<address>::operator size_t();
	}
};

template<std::uintptr_t address>
struct register_write : public register_unknown<address> {
public:
	template<typename T>
	[[gnu::always_inline]]
	register_write&
		operator=(T value)
	{
		return static_cast<register_write&>(register_unknown<address>::operator=(value));
	}

	[[gnu::always_inline]]
	register_write&
		operator=(std::size_t value)
	{
		return static_cast<register_write&>(register_unknown<address>::operator=(value));
	}

	template<typename T>
	[[gnu::always_inline]]
	register_write&
		operator|=(T value)
	{
		return static_cast<register_write&>(register_unknown<address>::operator|=(value));
	}

	[[gnu::always_inline]]
	register_write&
		operator|=(std::size_t value)
	{
		return static_cast<register_write&>(register_unknown<address>::operator|=(value));
	}
};
