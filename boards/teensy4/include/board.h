#include "inttypes.h"
#include "stddef.h"

/** Mark code or data as residing on boot storage
 * This code and data can be used before main.
 */
#define SECTION_CODE_BOOT [[gnu::section(".flashCode")]]
#define SECTION_DATA_BOOT [[gnu::section(".flashData")]]

/** Mark code or data as residing on boot storage
 * This code and data can't be used before 'main()'.
 */
#define SECTION_CODE_FAST // Default on this board.
#define SECTION_DATA_FAST // Default on this board.

/** Internal Memory starting address.
 * Absolute address of internal memory.
 */
extern size_t __board_iram;
#define BOARD_IRAM ((void*)&__board_iram)

/** First free byte of Internal Memory.
 * Absolute address of the first unused byte in internal memory.
 */
extern size_t __board_iram_free;
#define BOARD_IRAM_FREE ((void*)&__board_iram_free)

/** Size of Internal Memory
 * Absolute size of internal memory. Can be 0.
 */
extern size_t __board_iram_size;
#define BOARD_IRAM_SIZE ((size_t) & __board_iram_size)

/** Mark code or data as residing in Internal Memory
 * This code and data can't be used before 'main()'.
 */
#define SECTION_CODE_IRAM [[gnu::section(".iramCode")]]
#define SECTION_DATA_IRAM [[gnu::section(".iramData")]]

/** External Memory starting address.
 * Absolute address of internal memory.
 */
extern size_t __board_eram;
#define BOARD_ERAM ((void*)&__board_eram)

/** First free byte of External Memory.
 * Absolute address of the first unused byte in internal memory.
 */
extern size_t __board_eram_free;
#define BOARD_ERAM_FREE ((void*)&__board_eram_free)

/** Size of External Memory
 * Absolute size of external memory. Can be 0.
 */
extern size_t __board_eram_size;
#define BOARD_ERAM_SIZE ((size_t) & __board_eram_size)

/** Mark code or data as residing in External Memory
 * This code and data can't be used before 'main()'.
 */
#define SECTION_CODE_ERAM [[gnu::section(".eramCode")]]
#define SECTION_DATA_ERAM [[gnu::section(".eramData")]]
