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
#import "cinttypes"
#import "cstddef"

template<uintptr_t address>
struct register_unknown {
public:
	static volatile inline size_t& ref = *reinterpret_cast<size_t*>(address);

protected:
	template<typename _T>
	[[gnu::always_inline]]
	register_unknown&
		operator=(_T value) noexcept
	{
		ref = value;
		return *this;
	}

	template<typename _T>
	[[gnu::always_inline]]
	register_unknown&
		operator|=(_T value) noexcept
	{
		ref |= value;
		return *this;
	}

	template<typename _T>
	[[gnu::always_inline]]
	register_unknown&
		operator&=(_T value) noexcept
	{
		ref &= value;
		return *this;
	}

	template<typename _T>
	[[gnu::always_inline]] operator _T() const noexcept
	{
		return static_cast<_T>(ref);
	}

	template<typename _T>
	[[gnu::always_inline]] operator size_t() const noexcept
	{
		return ref;
	}
};

template<std::uintptr_t address>
struct register_read_write : public register_unknown<address> {
public:
	template<typename _T>
	[[gnu::always_inline]] operator _T() const noexcept
	{
		return register_unknown<address>::operator _T();
	}

	template<typename _T>
	[[gnu::always_inline]]
	register_read_write&
		operator=(_T value) noexcept
	{
		return static_cast<register_read_write&>(register_unknown<address>::operator=(value));
	}

	template<typename _T>
	[[gnu::always_inline]]
	register_read_write&
		operator|=(_T value) noexcept
	{
		return static_cast<register_read_write&>(register_unknown<address>::operator|=(value));
	}

	template<typename _T>
	[[gnu::always_inline]]
	register_read_write&
		operator&=(_T value) noexcept
	{
		return static_cast<register_read_write&>(register_unknown<address>::operator&=(value));
	}
};

template<std::uintptr_t address>
struct register_read : public register_unknown<address> {
public:
	template<typename _T>
	register_read& operator=(_T value) = delete;

	template<typename _T>
	[[gnu::always_inline]] operator _T() const noexcept
	{
		return register_unknown<address>::operator _T();
	}
};

template<std::uintptr_t address>
struct register_write : public register_unknown<address> {
public:
	template<typename _T>
	[[gnu::always_inline]]
	register_write&
		operator=(_T value) noexcept
	{
		return static_cast<register_write&>(register_unknown<address>::operator=(value));
	}

	template<typename _T>
	[[gnu::always_inline]]
	register_write&
		operator|=(_T value) noexcept
	{
		return static_cast<register_write&>(register_unknown<address>::operator|=(value));
	}

	template<typename _T>
	[[gnu::always_inline]]
	register_write&
		operator&=(_T value) noexcept
	{
		return static_cast<register_write&>(register_unknown<address>::operator&=(value));
	}
};
