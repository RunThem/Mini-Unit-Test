#pragma once

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define __grey(msg)   "\033[30m" msg "\033[0m"
#define __red(msg)    "\033[31m" msg "\033[0m"
#define __green(msg)  "\033[32m" msg "\033[0m"
#define __yellow(msg) "\033[33m" msg "\033[0m"
#define __blue(msg)   "\033[34m" msg "\033[0m"
#define __color_size  (strlen(__grey("")))

#define __prompt      "************************************************************************"
#define __prompt_size (strlen(__prompt))

#define __fmt(buf, fmt, ...) snprintf(buf, sizeof(buf), fmt, ##__VA_ARGS__)
#define __dis(fmt, ...)      fprintf(stderr, fmt "\n", ##__VA_ARGS__)

typedef struct {
  long tests;
  long fails;
} __mut_result_t;

#define mut_assert(expr)                                                                           \
  do {                                                                                             \
    ++(result->tests);                                                                             \
    if (expr) {                                                                                    \
      ++(result->fails);                                                                           \
      __dis("        %s:%d (%s)", __FILE__, __LINE__, #expr);                                      \
    }                                                                                              \
  } while (0)

#define mut_test(func)  void func(__mut_result_t* result)
#define mut_group(func) void func(__mut_result_t* result)

#define mut_init(msg)                                                                              \
  __mut_result_t result = {0};                                                                     \
                                                                                                   \
  __dis(__prompt);                                                                                 \
  __dis("%*s", (int)(__prompt_size + strlen(msg)) / 2, msg);                                       \
  __dis(__prompt);

#define mut_add_test(func, comment)                                                                \
  extern void func(__mut_result_t*);                                                               \
                                                                                                   \
  do {                                                                                             \
    __mut_result_t __result = {0};                                                                 \
                                                                                                   \
    __dis("    %s:", #func);                                                                       \
                                                                                                   \
    (func)(&__result);                                                                             \
                                                                                                   \
    __dis("    -- pass: " __green("%-5zu") " fail: " __red("%-37zu") "\n",                         \
          __result.tests - __result.fails,                                                         \
          __result.fails);                                                                         \
                                                                                                   \
    result->tests += __result.tests;                                                               \
    result->fails += __result.fails;                                                               \
  } while (0)

#define mut_add_group(func, comment)                                                               \
  extern void func(__mut_result_t*);                                                               \
                                                                                                   \
  do {                                                                                             \
    __mut_result_t __result = {0};                                                                 \
                                                                                                   \
    __dis(__yellow("%s") ":", comment);                                                            \
                                                                                                   \
    (func)(&__result);                                                                             \
                                                                                                   \
    __dis("passed (" __green("%zu") "/%zu)\n", __result.tests - __result.fails, __result.tests);   \
                                                                                                   \
    result.tests += __result.tests;                                                                \
    result.fails += __result.fails;                                                                \
  } while (0)

#define mut_results()                                                                              \
  do {                                                                                             \
    size_t n      = 0;                                                                             \
    char buf[150] = {0};                                                                           \
                                                                                                   \
    __dis(__prompt);                                                                               \
                                                                                                   \
    n = __fmt(buf,                                                                                 \
              "TESTS PASSED (" __green("%zu") "/%zu) ",                                            \
              result.tests - result.fails,                                                         \
              result.tests);                                                                       \
                                                                                                   \
    __dis("%*s", (int)(__prompt_size + n + __color_size) / 2, buf);                                \
                                                                                                   \
    __dis(__prompt);                                                                               \
  } while (0)

#ifdef __cplusplus
} /* extern "C" */
#endif
