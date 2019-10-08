#ifdef INCLUDED_BASICS
#  error duplicate include: BASICS
#endif
#define INCLUDED_BASICS


#include <stdint.h>

// linkage keywords that make sense

#define internal static
#define external extern


// typedefs

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef float    f32;
typedef double   f64;


// array length and iteration macros

#define len(xs) \
	(sizeof(xs)/sizeof(xs[0]))

#define each(x, xs) \
	for (auto *x = xs; x < xs + sizeof(xs)/sizeof(xs[0]); ++x)

#define each_backwards(x, xs) \
	for (auto *x = xs + sizeof(xs)/sizeof(xs[0]) - 1; x >= xs ; --x)


// print

#define print(fmt, ...) \
	printf("%s:%d \t" fmt "\n", __FILE__, __LINE__, __VA_ARGS__)
