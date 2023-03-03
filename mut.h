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
#  define MUT_FLOAT_TOLERANCE (0.001)
#endif /* !MUT_FLOAT_TOLERANCE */

static inline bool __integer(intmax_t a, intmax_t b) {
  return a == b;
}

static inline bool __uninteger(uintmax_t a, uintmax_t b) {
  return a == b;
}

static inline bool __pointer(void* a, void* b) {
  return a == b;
}

static inline bool __float(float a, float b) {
  return fabsf(a - b) <= MUT_FLOAT_TOLERANCE;
}

static inline bool __string(const char* a, const char* b) {
  return !strcmp(a, b);
}

typedef uint64_t __us_t;
static inline char* __time_fmt(__us_t t) {
  static char buf[10] = {0};

  bzero(buf, sizeof(buf));
  if (t > (__us_t)60 * 60 * 1000 * 1000 * 1000) {
    snprintf(buf, sizeof(buf), "%6.2f h", 1.0 * t / ((__us_t)60 * 60 * 1000 * 1000 * 1000));
  } else if (t > (__us_t)60 * 1000 * 1000 * 1000) {
    snprintf(buf, sizeof(buf), "%6.2f m", 1.0 * t / ((__us_t)60 * 1000 * 1000 * 1000));
  } else if (t > (__us_t)1000 * 1000 * 1000) {
    snprintf(buf, sizeof(buf), "%6.2f s", 1.0 * t / ((__us_t)1000 * 1000 * 1000));
  } else if (t > (__us_t)1000 * 1000) {
    snprintf(buf, sizeof(buf), "%6.2f ms", 1.0 * t / ((__us_t)1000 * 1000));
  } else if (t > (__us_t)1000) {
    snprintf(buf, sizeof(buf), "%6.2f us", 1.0 * t / ((__us_t)1000));
  } else {
    snprintf(buf, sizeof(buf), "%6ld ns", t);
  }

  return (char*)buf;
}

/* clang-format off */
#define _mut_equal(a, b) _Generic((b),                                                             \
char                    : __integer,                                                               \
_Bool                   : __uninteger,                                                             \
signed char             : __integer,                                                               \
unsigned char           : __uninteger,                                                             \
signed short int        : __integer,                                                               \
unsigned short int      : __uninteger,                                                             \
signed int              : __integer,                                                               \
unsigned int            : __uninteger,                                                             \
signed long int         : __integer,                                                               \
unsigned long int       : __uninteger,                                                             \
signed long long int    : __integer,                                                               \
unsigned long long int  : __uninteger,                                                             \
void*                   : __pointer,                                                               \
float                   : __float,                                                                 \
double                  : __float,                                                                 \
long double             : __float,                                                                 \
char*                   : __string)(a, b)

#define _mut_type_fmt(a) _Generic((a),                                                             \
char                    : "\'%c\'",                                                                \
_Bool                   : "%d",                                                                    \
signed char             : "%hhd",                                                                  \
unsigned char           : "%hhu",                                                                  \
signed short int        : "%hd",                                                                   \
unsigned short int      : "%hu",                                                                   \
signed int              : "%d",                                                                    \
unsigned int            : "%u",                                                                    \
signed long int         : "%ld",                                                                   \
unsigned long int       : "%lu",                                                                   \
signed long long int    : "%lld",                                                                  \
unsigned long long int  : "%llu",                                                                  \
void*                   : "%p",                                                                    \
float                   : "%lf",                                                                   \
double                  : "%lf",                                                                   \
long double             : "%Lf",                                                                   \
char*                   : "\"%s\"")
/* clang-format on */

#define _grey(s)   "\033[30m" s "\033[0m"
#define _red(s)    "\033[31m" s "\033[0m"
#define _green(s)  "\033[32m" s "\033[0m"
#define _yellow(s) "\033[33m" s "\033[0m"
#define _blue(s)   "\033[34m" s "\033[0m"

#define _ps   "************************************************************************"
#define _ps_s (sizeof(_ps) - 1)

#define _p_s(buf, fmt, ...) snprintf(buf, sizeof(buf), fmt, ##__VA_ARGS__)
#define _p                  printf

typedef struct {
  size_t tests;
  size_t fails;
} __mut_result_t;

/* prototype to assert equal. */
#define mut_equal(a, b)                                                                            \
  do {                                                                                             \
    ++(result->tests);                                                                             \
    if (!_mut_equal(a, b)) {                                                                       \
      ++(result->fails);                                                                           \
      char fmt[72] = {0};                                                                          \
      _p_s(fmt,                                                                                    \
           "        %s:%d (%s != %s)\n",                                                           \
           __FILE__,                                                                               \
           __LINE__,                                                                               \
           _mut_type_fmt(a),                                                                       \
           _mut_type_fmt(b));                                                                      \
      _p(fmt, (a), (b));                                                                           \
    }                                                                                              \
  } while (0)

/* assert a true statement. */
#define mut_assert(expr)                                                                           \
  do {                                                                                             \
    ++(result->tests);                                                                             \
    if (!(expr)) {                                                                                 \
      ++(result->fails);                                                                           \
      _p("        %s:%d (%s)\n", __FILE__, __LINE__, #expr);                                       \
    }                                                                                              \
  } while (0)

/* benchmark statement. */
#define mut_blank_line()
#define mut_bench(msg, expr_block)                                                                 \
  do {                                                                                             \
    size_t MUT_N  = 1;                                                                             \
    clock_t start = 0, end = 0;                                                                    \
    while ((end - start) < 100000 /* 0.1s */) {                                                    \
      MUT_N *= 10;                                                                                 \
      start = clock();                                                                             \
      for (size_t count = 0; count < MUT_N; count++) {                                             \
        expr_block;                                                                                \
      }                                                                                            \
      end = clock();                                                                               \
    }                                                                                              \
    _p("        %s:%d { " _blue("%s") ", " _blue("%s") " }\n",                                     \
       __FILE__,                                                                                   \
       __LINE__,                                                                                   \
       __time_fmt(end - start),                                                                    \
       __time_fmt((end - start) * 1000 / MUT_N));                                                  \
    result->tests++;                                                                               \
  } while (0)

#define mut_test(func)   void(func)(__mut_result_t * result)
#define mut_group(func)  void(func)(__mut_result_t * result)
#define mut_extern(func) extern void(func)(__mut_result_t * result)

#define mut_init(msg)                                                                              \
  __mut_result_t result = {0};                                                                     \
  clock_t start         = clock();                                                                 \
  _p(_ps "\n%*s\n" _ps "\n\n", (int)(_ps_s + strlen(msg)) / 2, msg);

#define mut_add_test(func, comment)                                                                \
  do {                                                                                             \
    _p("    %s:\n", #func);                                                                        \
    const clock_t start    = clock();                                                              \
    __mut_result_t _result = {0};                                                                  \
    (func)(&_result);                                                                              \
    _p("    -- pass: " _green("%-5zu") " fail: " _red("%-37zu") _blue("%s") "\n\n",                \
       _result.tests - _result.fails,                                                              \
       _result.fails,                                                                              \
       __time_fmt((clock() - start) * 1000));                                                      \
    result->tests += _result.tests;                                                                \
    result->fails += _result.fails;                                                                \
  } while (0)

#define mut_add_group(func, comment)                                                               \
  do {                                                                                             \
    _p(_yellow("%s") ":\n", comment);                                                              \
    __mut_result_t _result = {0};                                                                  \
    (func)(&_result);                                                                              \
    _p("tests passed (" _green("%zu") "/%zu)\n\n", _result.tests - _result.fails, _result.tests);  \
    result.tests += _result.tests;                                                                 \
    result.fails += _result.fails;                                                                 \
  } while (0)

#define mut_results()                                                                              \
  do {                                                                                             \
    size_t n      = 0;                                                                             \
    char buf[150] = {0};                                                                           \
    _p(_ps "\n\n");                                                                                \
    n = _p_s(buf,                                                                                  \
             "TESTS PASSED (" _green("%zu") "/%zu) time: " _blue("%s") "",                         \
             result.tests - result.fails,                                                          \
             result.tests,                                                                         \
             __time_fmt((clock() - start) * 1000));                                                \
    _p("%*s\n\n" _ps "\n", (int)(_ps_s + n + 18) / 2, buf);                                        \
  } while (0)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !MINI_UNIT_TEST_H */
