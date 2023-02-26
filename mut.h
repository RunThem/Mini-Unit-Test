/**
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 **/

#ifndef MINI_UNIT_TEST_H
#define MINI_UNIT_TEST_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MUT_FLOAT_TOLERANCE
#  define MUT_FLOAT_TOLERANCE (0.00001)
#endif /* !MUT_FLOAT_TOLERANCE */

static inline bool mut_equal_signed_integer(intmax_t a, intmax_t b) {
  return a == b;
}

static inline bool mut_equal_unsigned_integer(uintmax_t a, uintmax_t b) {
  return a == b;
}

static inline bool mut_equal_pointer(void* a, void* b) {
  return a == b;
}

static inline bool mut_equal_float(float a, float b) {
  return fabsf(a - b) <= MUT_FLOAT_TOLERANCE;
}

static inline bool mut_equal_string(const char* a, const char* b) {
  return !strcmp(a, b);
}

/* clang-format off */
#define _mut_equal(a, b) _Generic((a),                                                           \
char                    : mut_equal_signed_integer,                                              \
_Bool                   : mut_equal_unsigned_integer,                                            \
signed char             : mut_equal_signed_integer,                                              \
unsigned char           : mut_equal_unsigned_integer,                                            \
signed short int        : mut_equal_signed_integer,                                              \
unsigned short int      : mut_equal_unsigned_integer,                                            \
signed int              : mut_equal_signed_integer,                                              \
unsigned int            : mut_equal_unsigned_integer,                                            \
signed long int         : mut_equal_signed_integer,                                              \
unsigned long int       : mut_equal_unsigned_integer,                                            \
signed long long int    : mut_equal_signed_integer,                                              \
unsigned long long int  : mut_equal_unsigned_integer,                                            \
void*                   : mut_equal_pointer,                                                     \
float                   : mut_equal_float,                                                       \
double                  : mut_equal_float,                                                       \
long double             : mut_equal_float,                                                       \
char*                   : mut_equal_string)(a, b)

#define _mut_type_fmt(a) _Generic((a),                                                            \
char                    : "\'%c\'",                                                               \
_Bool                   : "%d",                                                                   \
signed char             : "%hhd",                                                                 \
unsigned char           : "%hhu",                                                                 \
signed short int        : "%hd",                                                                  \
unsigned short int      : "%hu",                                                                  \
signed int              : "%d",                                                                   \
unsigned int            : "%u",                                                                   \
signed long int         : "%ld",                                                                  \
unsigned long int       : "%lu",                                                                  \
signed long long int    : "%lld",                                                                 \
unsigned long long int  : "%llu",                                                                 \
void*                   : "%p",                                                                   \
float                   : "%lf",                                                                  \
double                  : "%lf",                                                                  \
long double             : "%Lf",                                                                  \
char*                   : "\"%s\"")
/* clang-format on */

static size_t ltests = 0;
static size_t lfails = 0;

#define mut_tests(name) static void name(void)

/* prototype to assert equal. */
#define mut_equal(a, b)                                                                            \
  do {                                                                                             \
    ++ltests;                                                                                      \
    if (!_mut_equal(a, b)) {                                                                       \
      ++lfails;                                                                                    \
      char fmt[72] = {0};                                                                          \
      sprintf(fmt,                                                                                 \
              "\t%s:%d (%s != %s)\n",                                                              \
              __FILE__,                                                                            \
              __LINE__,                                                                            \
              _mut_type_fmt(a),                                                                    \
              _mut_type_fmt(b));                                                                   \
      printf(fmt, (a), (b));                                                                       \
    }                                                                                              \
  } while (0)

/* assert a true statement. */
#define mut_assert(expr)                                                                           \
  do {                                                                                             \
    if (!(expr)) {                                                                                 \
      printf("\t%s:%d (%s)\n", __FILE__, __LINE__, #expr);                                         \
    }                                                                                              \
  } while (0)

/* run a test. */
#define mut_run(test, comment)                                                                        \
  do {                                                                                                \
    const size_t ts     = ltests;                                                                     \
    const size_t fs     = lfails;                                                                     \
    const clock_t start = clock();                                                                    \
    printf("%s (%s):\n", #test, comment);                                                             \
    test();                                                                                           \
    printf(                                                                                           \
        "-- pass: \033[32m%-20zu\033[0m fail: \033[31m%-20zu\033[0m time: \033[34m%ld\033[0m ms\n\n", \
        (ltests - ts) - (lfails - fs),                                                                \
        lfails - fs,                                                                                  \
        (long)((clock() - start) * 1000 / CLOCKS_PER_SEC));                                           \
  } while (0)

/* display the test results. */
#define mut_results()                                                                              \
  do {                                                                                             \
    if (lfails == 0) {                                                                             \
      printf("ALL TESTS PASSED (\033[32m%zu\033[0m/%zu)\n", ltests, ltests);                       \
    } else {                                                                                       \
      printf("SOME TESTS FAILED (\033[32m%zu\033[0m/%zu)\n", ltests - lfails, ltests);             \
    }                                                                                              \
  } while (0)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !MINI_UNIT_TEST_H */