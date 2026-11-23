#ifndef TYPES
#define TYPES

#include <inttypes.h>
#include <stdint.h>

// ints
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// unsigned ints
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#endif // !TYPES
// print ints
#ifndef D64
#define D64 "%" PRId64 "" // int
#endif
#ifndef D32
#define D32 "%" PRId32 ""
#endif
#ifndef D16
#define D16 "%" PRId16 ""
#endif
#ifndef D8
#define D8 "%" PRId8 ""
#endif

#ifndef U64
#define U64 "%" PRud64 "" // uint
#endif
#ifndef U32
#define U32 "%" PRIu32 ""
#endif
#ifndef U16
#define U16 "%" PRIu16 ""
#endif
#ifndef U8
#define U8 "%" PRIu8 ""
#endif

#ifndef X64
#define X64 "%" PRux64 "" // hex
#endif
#ifndef X32
#define X32 "%" PRIx32 ""
#endif
#ifndef X16
#define X16 "%" PRIx16 ""
#endif
#ifndef X8
#define X8 "%" PRIx8 ""
#endif
