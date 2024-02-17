#include "string.h"
#include <cinttypes>
#include <cstddef>
#include "board.h"

[[gnu::always_inline]]
void* _memcpy(void* dest, const void* src, std::size_t count)
{
	// We can do this in several ways:
	// - 8 byte wide copies with LDRD/SDRD. (0.5 cycles per 32bit)
	// - 4 byte wide copies with LDR/SDR. (1 cycles per 32bit)
	// - 2 byte wide copies with LDRH/SDRH. (2 cycles per 32bit)
	// - 1 byte wide copies with LDRB/SDRB. (4 cycles per 32bit)
	// Realisticly, we only want to the 8, 4 and 1 byte transfers.

	// Exit if this is the exact same address.
	if (dest == src) {
		return dest;
	}

	// Calculate the remainders after each transfer occurs.
	std::size_t rem8      = count % 8; // and
	std::size_t num8      = count / 8; // lsrs
	std::size_t num1      = rem8 % 4;
	std::size_t num4      = rem8 / 4;
	int8_t      isAligned = (reinterpret_cast<size_t>(dest) % sizeof(uint32_t) == 0) && (reinterpret_cast<size_t>(src) % sizeof(uint32_t) == 0);

	// Do the DoubleWord copies
	void* endDW = reinterpret_cast<uint32_t*>(dest) + (num8 * 2);
	if (isAligned && (num8 > 0)) {
		// Must be word aligned, or we crash.
#if 1
		// LLVM does not use LDRD/STRD, which is significantly faster.
		__asm volatile(R"(
	pli [%[src]]
1:	pli [%[src], #+32]
	ldrd r0, r1, [%[src]]
	strd r0, r1, [%[dest]]
	add %[src], 8
	add %[dest], 8
	cmp %[dest], %[end]
	bne 1b
)"
					   : [dest] "+r"(dest), [src] "+r"(src)
					   : [end] "r"(endDW)
					   : "r0", "r1", "memory");
#else
		uint32_t*       destW = reinterpret_cast<uint32_t*>(dest);
		const uint32_t* srcW  = reinterpret_cast<const uint32_t*>(src);
		for (; destW < endDW; destW += 1, srcW += 1) {
			*destW = *srcW;
		}

#endif
	}

	// Do the Word copies
	void* endW = reinterpret_cast<uint32_t*>(endDW) + num4;
	if (!isAligned || (num4 > 0)) {
#if 0
		__asm volatile(R"(
	pli [%[src]]
1:	pli [%[src], #+32]
	ldr r0, [%[src]]
	str r0, [%[dest]]
	add %[src], 4
	add %[dest], 4
	cmp %[dest], %[end]
	bne 1b
)"
					   : [dest] "+r"(dest), [src] "+r"(src)
					   : [end] "r"(endW)
					   : "r0", "r1", "memory");
#else
		uint32_t*       destW = reinterpret_cast<uint32_t*>(dest);
		const uint32_t* srcW  = reinterpret_cast<const uint32_t*>(src);
		for (; destW < endW; destW += 1, srcW += 1) {
			*destW = *srcW;
		}
#endif
	}

	// Do the Byte copies
	void* endB = reinterpret_cast<uint8_t*>(dest) + count;
	if (num1 > 0) {
#if 0
		__asm volatile(R"(
	pli [%[src]]
1:	pli [%[src], #+32]
	ldrb r0, [%[src]]
	strb r0, [%[dest]]
	add %[src], 1
	add %[dest], 1
	cmp %[dest], %[end]
	bne 1b
)"
					   : [dest] "+r"(dest), [src] "+r"(src)
					   : [end] "r"(endB)
					   : "r0", "r1", "memory");
#else
		uint8_t*       destW = reinterpret_cast<uint8_t*>(dest);
		const uint8_t* srcW  = reinterpret_cast<const uint8_t*>(src);
		for (; destW < endB; destW += 1, srcW += 1) {
			*destW = *srcW;
		}
#endif
	}

	return dest;
}

extern "C" SECTION_CODE_FAST
void* memcpy(void* dest, const void* src, size_t count)
{
	return _memcpy(dest, src, count);
};

extern "C" SECTION_CODE_BOOT [[gnu::noinline]]
void* boot_memcpy(void* dest, const void* src, size_t count)
{
	return _memcpy(dest, src, count);
};

[[gnu::always_inline]]
void* _memset(void* dest, uint8_t value, std::size_t count)
{
	// We can do this in several ways:
	// - 8 byte wide copies with LDRD/SDRD. (0.5 cycles per 32bit)
	// - 4 byte wide copies with LDR/SDR. (1 cycles per 32bit)
	// - 2 byte wide copies with LDRH/SDRH. (2 cycles per 32bit)
	// - 1 byte wide copies with LDRB/SDRB. (4 cycles per 32bit)
	// Realisticly, we only want to the 8, 4 and 1 byte transfers.

	// Calculate the remainders after each transfer occurs.
	std::size_t rem8      = count % 8;
	std::size_t num8      = count / 8;
	std::size_t num1      = rem8 % 4;
	std::size_t num4      = rem8 / 4;
	bool        isAligned = ((std::size_t)dest % sizeof(uint32_t) == 0);

	std::size_t valueW = (value << 24) | (value << 16) | (value << 8) | value;

	// Do the DoubleWord copies
	void* endDW = reinterpret_cast<uint32_t*>(dest) + num8 * 2;
	if (isAligned && (num8 > 0)) {
		// Must be aligned, or this crashes.
#if 1
		// LLVM does not use STRD, which is significantly faster.
		__asm volatile(R"(
1:	strd %[value], %[value], [%[dest]]
	add %[dest], 8
	cmp %[dest], %[end]
	bne 1b
)"
					   : [dest] "+r"(dest)
					   : [end] "r"(endDW), [value] "r"(valueW)
					   : "memory");
#else
		uint32_t* destW = reinterpret_cast<uint32_t*>(dest);
		for (; destW < endDW; destW += 2) {
			*destW       = valueW;
			*(destW + 1) = valueW;
		}
#endif
	}

	// Do the Word copies
	void* endW = reinterpret_cast<uint32_t*>(endDW) + num4;
	if (!isAligned || (num4 > 0)) {
#if 0
		__asm volatile(R"(
1:	str %[value], [%[dest]]
	add %[dest], 4
	cmp %[dest], %[end]
	bne 1b
)"
					   : [dest] "+r"(dest)
					   : [end] "r"(endW), [value] "r"(valueW)
					   : "memory");
#else
		uint32_t* destW = reinterpret_cast<uint32_t*>(dest);
		for (; destW < endW; destW += 1) {
			*destW = valueW;
		}
#endif
	}

	// Do the Byte copies
	void* endB = reinterpret_cast<uint8_t*>(dest) + count;
	if (num1 > 0) {
#if 0
		__asm volatile(R"(
1:	strb %[value], [%[dest]]
	add %[dest], 1
	cmp %[dest], %[end]
	bne 1b
)"
					   : [dest] "+r"(dest)
					   : [end] "r"(endB), [value] "r"(value)
					   : "memory");
#else
		uint8_t* destW = reinterpret_cast<uint8_t*>(dest);
		for (; destW < endB; destW += 1) {
			*destW = valueW;
		}
#endif
	}

	return dest;
}

extern "C" SECTION_CODE_FAST
void* memset(void* dest, uint8_t value, size_t count)
{
	return _memset(dest, value, count);
}

extern "C" SECTION_CODE_BOOT [[gnu::noinline]]
void* boot_memset(void* dest, uint8_t value, size_t count)
{
	return _memset(dest, value, count);
}
