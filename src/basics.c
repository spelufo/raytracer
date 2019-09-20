#ifdef INCLUDED_BASICS
#  error duplicate include: BASICS
#endif
#define INCLUDED_BASICS


// linkage keywords that make sense

#define internal static
#define external extern


// typedefs

typedef unsigned char byte;


// array length and iteration macros

#define len(xs) (sizeof(xs)/sizeof(xs[0]))
#define each(x, xs) for (auto *x = xs; x < xs + sizeof(xs)/sizeof(xs[0]); ++x)
#define each_backwards(x, xs) for (auto *x = xs + sizeof(xs)/sizeof(xs[0]) - 1; x >= xs ; --x)
