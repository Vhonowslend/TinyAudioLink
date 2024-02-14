#pragma once
#include <cinttypes>
#include <cstddef>

template<std::size_t address>
struct registerUndefined {
	private:
	static volatile inline std::size_t& ref = *reinterpret_cast<volatile std::size_t*>(address);

	protected:
	[[gnu::always_inline]] registerUndefined& operator=(std::size_t value)
	{
		ref = value;
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
	[[gnu::always_inline]] registerReadWrite& operator=(T value)
	{
		return static_cast<registerReadWrite&>(registerUndefined<address>::operator=(value));
	}

	[[gnu::always_inline]] registerReadWrite& operator=(std::size_t value)
	{
		return static_cast<registerReadWrite&>(registerUndefined<address>::operator=(value));
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
	[[gnu::always_inline]] registerWriteOnly& operator=(T value)
	{
		return static_cast<registerWriteOnly&>(registerUndefined<address>::operator=(value));
	}

	[[gnu::always_inline]] registerWriteOnly& operator=(std::size_t value)
	{
		return static_cast<registerWriteOnly&>(registerUndefined<address>::operator=(value));
	}
};
