#pragma once
#import "cinttypes"
#import "cstddef"

namespace xmr {
	/** ARM Specialized Atomics
	 * 
	 * ToDo: Add a 2nd lock value for multi-threading.
	 */
	template<typename __type>
	class atomic {
		volatile __type _value;

	public:
		typedef __type valtype;

		[[gnu::always_inline]] ~atomic() {}

		[[gnu::always_inline]] atomic() : _value(0) {}

		[[gnu::always_inline]] atomic(__type value) : _value(value) {}

		// Copy Constructor
		[[gnu::always_inline]] atomic(xmr::atomic<__type>& rhs) : _value(static_cast<__type>(rhs)) {}

		// Move Constructor
		[[gnu::always_inline]] atomic(xmr::atomic<__type> const& rhs) : _value(static_cast<__type>(rhs)) {}

	public /* Base */:
		// Conversion
		[[gnu::always_inline]] operator __type()
		{
			__type value;
			if constexpr (sizeof(__type) == 1) {
				value = __builtin_arm_ldrex(&_value);
			} else if constexpr (sizeof(__type) == 2) {
				value = __builtin_arm_ldrex(&_value);
			} else if constexpr (sizeof(__type) == 4) {
				value = __builtin_arm_ldrex(&_value);
			} else if constexpr (sizeof(__type) == 8) {
				value = __builtin_arm_ldrex(&_value);
			} else {
				value = 0;
			}
			__builtin_arm_clrex();

			return value;
		}

		// Assignment
		[[gnu::always_inline]]
		xmr::atomic<__type>&
			operator=(__type value)
		{
			return *this;
		}

		[[gnu::always_inline]]
		xmr::atomic<__type>&
			operator+=(__type pvalue)
		{
			asm volatile("msr basepri, %[val]" : : [val] "r"(0xFF));

			__type value;
			if constexpr (sizeof(__type) == 1) {
				value = __builtin_arm_ldrex(&_value);
			} else if constexpr (sizeof(__type) == 2) {
				value = __builtin_arm_ldrex(&_value);
			} else if constexpr (sizeof(__type) == 4) {
				value = __builtin_arm_ldrex(&_value);
			} else if constexpr (sizeof(__type) == 8) {
				value = __builtin_arm_ldrex(&_value);
			} else {
				value = 0;
			}

			value += pvalue;

			size_t status;
			if constexpr (sizeof(__type) == 1) {
				__builtin_arm_strex(value, &_value);
			} else if constexpr (sizeof(__type) == 2) {
				__builtin_arm_strex(value, &_value);
			} else if constexpr (sizeof(__type) == 4) {
				__builtin_arm_strex(value, &_value);
			} else if constexpr (sizeof(__type) == 8) {
				__builtin_arm_strex(value, &_value);
			}
			__builtin_arm_clrex();

			asm volatile("msr basepri, %[val]" : : [val] "r"(0x0));

			return *this;
		}

		[[gnu::always_inline]]
		xmr::atomic<__type>&
			operator-=(__type pvalue)
		{
			asm volatile("msr basepri, %[val]" : : [val] "r"(0xFF));

			__type value;
			if constexpr (sizeof(__type) == 1) {
				value = __builtin_arm_ldrex(&_value);
			} else if constexpr (sizeof(__type) == 2) {
				value = __builtin_arm_ldrex(&_value);
			} else if constexpr (sizeof(__type) == 4) {
				value = __builtin_arm_ldrex(&_value);
			} else if constexpr (sizeof(__type) == 8) {
				value = __builtin_arm_ldrex(&_value);
			} else {
				value = 0;
			}

			value -= pvalue;

			size_t status;
			if constexpr (sizeof(__type) == 1) {
				__builtin_arm_strex(value, &_value);
			} else if constexpr (sizeof(__type) == 2) {
				__builtin_arm_strex(value, &_value);
			} else if constexpr (sizeof(__type) == 4) {
				__builtin_arm_strex(value, &_value);
			} else if constexpr (sizeof(__type) == 8) {
				__builtin_arm_strex(value, &_value);
			}
			__builtin_arm_clrex();

			asm volatile("msr basepri, %[val]" : : [val] "r"(0x0));

			return *this;
		}

		// Pre-increment, -decrement
		[[gnu::always_inline]]
		xmr::atomic<__type>&
			operator++()
		{
			*this += 1;
			return *this;
		}

		[[gnu::always_inline]]
		xmr::atomic<__type>&
			operator--()
		{
			*this -= 1;
			return *this;
		}

		// Post-increment, -decrement (must return value)
		[[gnu::always_inline]]
		__type
			operator++(int)
		{
			__type value = static_cast<__type>(*this);
			++*this;
			return value;
		}

		[[gnu::always_inline]]
		__type
			operator--(int)
		{
			__type value = static_cast<__type>(*this);
			--*this;
			return value;
		}

		[[gnu::always_inline]]
		bool operator==(__type value)
		{
			return static_cast<__type>(*this) == value;
		}

		[[gnu::always_inline]]
		bool operator<=(__type value)
		{
			return static_cast<__type>(*this) <= value;
		}

		[[gnu::always_inline]]
		bool operator<(__type value)
		{
			return static_cast<__type>(*this) < value;
		}

		[[gnu::always_inline]]
		bool operator>=(__type value)
		{
			return static_cast<__type>(*this) >= value;
		}

		[[gnu::always_inline]]
		bool operator>(__type value)
		{
			return static_cast<__type>(*this) > value;
		}

	public /* Helpers */:
		[[gnu::always_inline]]
		xmr::atomic<__type>&
			operator+=(xmr::atomic<__type> const& value)
		{
			this += static_cast<__type>(value);
		}

		// Copy Assignment
		[[gnu::always_inline]]
		xmr::atomic<__type>&
			operator=(xmr::atomic<__type> const& value)
		{
			this = static_cast<__type>(value);
			return *this;
		};

		// Move Assignment
		[[gnu::always_inline]]
		xmr::atomic<__type>&
			operator=(xmr::atomic<__type>& rhs)
		{
			this = static_cast<__type>(rhs);
			return *this;
		};

		[[gnu::always_inline]]
		xmr::atomic<__type>&
			operator-=(xmr::atomic<__type> const& value)
		{
			this -= static_cast<__type>(value);
		}

		[[gnu::always_inline]]
		bool operator==(xmr::atomic<__type> const& value)
		{
			return this == (value.operator __type());
		};

		[[gnu::always_inline]]
		bool operator<=(xmr::atomic<__type> const& value)
		{
			return this <= (value.operator __type());
		};

		[[gnu::always_inline]]
		bool operator<(xmr::atomic<__type> const& value)
		{
			return this < (value.operator __type());
		};

		[[gnu::always_inline]]
		bool operator>=(xmr::atomic<__type> const& value)
		{
			return this >= (value.operator __type());
		};

		[[gnu::always_inline]]
		bool operator>(xmr::atomic<__type> const& value)
		{
			return this > (value.operator __type());
		};
	};

	typedef xmr::atomic<uint8_t>   atomic_uint8_t;
	typedef xmr::atomic<uint16_t>  atomic_uint16_t;
	typedef xmr::atomic<uint32_t>  atomic_uint32_t;
	typedef xmr::atomic<uint64_t>  atomic_uint64_t;
	typedef xmr::atomic<int8_t>    atomic_int8_t;
	typedef xmr::atomic<int16_t>   atomic_int16_t;
	typedef xmr::atomic<int32_t>   atomic_int32_t;
	typedef xmr::atomic<int64_t>   atomic_int64_t;
	typedef xmr::atomic<intptr_t>  atomic_intptr_t;
	typedef xmr::atomic<uintptr_t> atomic_uintptr_t;
	typedef xmr::atomic<size_t>    atomic_size_t;
	typedef xmr::atomic<void*>     atomic_ptr_t;
} // namespace xmr
