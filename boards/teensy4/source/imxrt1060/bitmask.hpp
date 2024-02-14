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
#include <cstddef>
#include <type_traits>

template<typename Enum>
struct enable_bitmask_operators {
	static const bool enable = false;
};

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum>::type operator|(Enum lhs, Enum rhs)
{
	using underlying = typename std::underlying_type<Enum>::type;
	return static_cast<Enum>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, Enum>::type operator&(Enum lhs, Enum rhs)
{
	using underlying = typename std::underlying_type<Enum>::type;
	return static_cast<Enum>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, bool>::type any(Enum lhs)
{
	using underlying = typename std::underlying_type<Enum>::type;
	return static_cast<underlying>(lhs) != static_cast<underlying>(0);
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, bool>::type exact(Enum lhs, Enum rhs)
{
	using underlying = typename std::underlying_type<Enum>::type;
	return static_cast<underlying>(lhs) == static_cast<underlying>(rhs);
}

template<typename Enum>
typename std::enable_if<enable_bitmask_operators<Enum>::enable, bool>::type has(Enum lhs, Enum rhs)
{
	using underlying = typename std::underlying_type<Enum>::type;
	return (lhs & rhs) == rhs;
}

#define P_ENABLE_BITMASK_OPERATORS(x)    \
	template<>                           \
	struct enable_bitmask_operators<x> { \
		static const bool enable = true; \
	};
