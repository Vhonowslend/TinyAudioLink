#include <inttypes.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void* memcpy(void* dest, const void* src, size_t count);

void* memset(void* dest, uint8_t value, size_t count);

void* boot_memcpy(void* dest, const void* src, size_t count);

void* boot_memset(void* dest, uint8_t value, size_t count);

#ifdef __cplusplus
}
#endif
