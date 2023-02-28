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

/* clang-format off */
#define _mut_equal(a, b) _Generic((a),                                                             \
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

#define _grey(s)   "\033[30;1m" s "\033[0m"
#define _red(s)    "\033[31m" s "\033[0m"
#define _green(s)  "\033[32m" s "\033[0m"
#define _yellow(s) "\033[33m" s "\033[0m"
#define _blue(s)   "\033[34m" s "\033[0m"

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
      sprintf(fmt,                                                                                 \
              "        " _grey("%s:%d") " (%s != %s)\n",                                           \
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
    ++(result->tests);                                                                             \
    if (!(expr)) {                                                                                 \
      ++(result->fails);                                                                           \
      printf("        " _grey("%s:%d") " (%s)\n", __FILE__, __LINE__, #expr);                      \
    }                                                                                              \
  } while (0)

#define _ps   "****************************************************"
#define _ps_s (sizeof(_ps) - 1)

#define mut_init(msg)                                                                              \
  __mut_result_t result = {0};                                                                     \
  clock_t start         = clock();                                                                 \
  printf(_ps "\n");                                                                                \
  printf("%*s\n", (int)(_ps_s + strlen(msg)) / 2, msg);                                            \
  printf(_ps "\n\n");

#define mut_test(func)        static void T_##func(__mut_result_t* result)
#define mut_extern_test(func) extern void T_##func(__mut_result_t* result)
#define mut_add_test(func, comment)                                                                \
  do {                                                                                             \
    printf("    %s (" _yellow("\"%s\"") "):\n", #func, comment);                                   \
    const clock_t start    = clock();                                                              \
    __mut_result_t _result = {0};                                                                  \
    T_##func(&_result);                                                                            \
    printf("    -- pass: " _green("%-10zu") " fail: " _red("%-10zu") " time: " _blue(              \
               "%ld") " ms\n\n",                                                                   \
           _result.tests - _result.fails,                                                          \
           _result.fails,                                                                          \
           (long)((clock() - start) * 1000 / CLOCKS_PER_SEC));                                     \
    result->tests += _result.tests;                                                                \
    result->fails += _result.fails;                                                                \
  } while (0)

#define mut_group(func)        static void G_##func(__mut_result_t* result)
#define mut_extern_group(func) extern void G_##func(__mut_result_t* result)
#define mut_add_group(func, comment)                                                               \
  do {                                                                                             \
    printf("%s ("_yellow("\"%s\"") "): \n", #func, comment);                                       \
    __mut_result_t _result = {0};                                                                  \
    G_##func(&_result);                                                                            \
    printf("tests passed (" _green("%zu") "/%zu)\n\n",                                             \
           _result.tests - _result.fails,                                                          \
           _result.tests);                                                                         \
    result.tests += _result.tests;                                                                 \
    result.fails += _result.fails;                                                                 \
  } while (0)

#define mut_all_results()                                                                          \
  do {                                                                                             \
    size_t n      = 0;                                                                             \
    char buf[150] = {0};                                                                           \
    printf(_ps "\n\n");                                                                            \
    n = snprintf(buf,                                                                              \
                 sizeof(buf),                                                                      \
                 "TESTS PASSED (" _green("%zu") "/%zu) time: " _blue("%ld") " ms",                 \
                 result.tests - result.fails,                                                      \
                 result.tests,                                                                     \
                 (long)((clock() - start) * 1000 / CLOCKS_PER_SEC));                               \
    printf("%*s\n\n", (int)(_ps_s + n + 18) / 2, buf);                                             \
    printf(_ps "\n");                                                                              \
  } while (0)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* !MINI_UNIT_TEST_H */
