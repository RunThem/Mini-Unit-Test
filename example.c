/**
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 **/

#include "mut.h"

mut_tests(test_mut) {
  char t_charX, t_charY;
  _Bool t_boolX, t_boolY;
  signed char t_i8X, t_i8Y;
  unsigned char t_u8X, t_u8Y;
  signed short int t_i16X, t_i16Y;
  unsigned short int t_u16X, t_u16Y;
  signed int t_i32X, t_i32Y;
  unsigned int t_u32X, t_u32Y;
  signed long int t_i64X, t_i64Y;
  unsigned long int t_u64X, t_u64Y;
  signed long long int t_illX, t_illY;
  unsigned long long int t_ullX, t_ullY;
  void *t_ptrX, *t_ptrY;
  float t_fX, t_fY;
  double t_lfX, t_lfY;
  long double t_llfX, t_llfY;
  char *t_strX, *t_strY;

#define test(v, v1, v2)                                                                            \
  do {                                                                                             \
    v##X = v##Y = (v1);                                                                            \
    mut_equal(v##X, v##Y);                                                                         \
    v##Y = (v2);                                                                                   \
    mut_equal(v##X, v##Y);                                                                         \
  } while (0)

  test(t_char, '1', '2');
  test(t_bool, true, false);

  test(t_i8, INT8_MAX, INT8_MAX - 1);
  test(t_u8, UINT8_MAX, UINT8_MAX - 1);
  test(t_i16, INT16_MAX, INT16_MAX - 1);
  test(t_u16, UINT16_MAX, UINT16_MAX - 1);
  test(t_i32, INT32_MAX, INT32_MAX - 1);
  test(t_u32, UINT32_MAX, UINT32_MAX - 1);
  test(t_i64, INT64_MAX, INT64_MAX - 1);
  test(t_u64, UINT64_MAX, UINT64_MAX - 1);
  test(t_ill, INTMAX_MAX, INTMAX_MAX - 1);
  test(t_ull, UINTMAX_MAX, UINTMAX_MAX - 1);

  test(t_ptr, (void*)&t_ptrX, (void*)&t_ptrY);

  test(t_f, 100000.0f, 100000.0f - 1.0f);
  test(t_lf, 100000.0l, 100000.0l - 1.0l);
  test(t_llf, 100000.0L, 100000.0L - 1.0L);

  test(t_str, "hello mut", "hello MUT");

  for (size_t i = 0; i < 100000000; i++) { }

  /** output:
   * test_mut (test Mini-Unit-Test library):
   *     example.c:34 ('1' != '2')
   *     example.c:35 (1 != 0)
   *     example.c:37 (127 != 126)
   *     example.c:38 (255 != 254)
   *     example.c:39 (32767 != 32766)
   *     example.c:40 (65535 != 65534)
   *     example.c:41 (2147483647 != 2147483646)
   *     example.c:42 (4294967295 != 4294967294)
   *     example.c:43 (9223372036854775807 != 9223372036854775806)
   *     example.c:44 (18446744073709551615 != 18446744073709551614)
   *     example.c:45 (9223372036854775807 != 9223372036854775806)
   *     example.c:46 (18446744073709551615 != 18446744073709551614)
   *     example.c:48 (0x7fffe042ace8 != 0x7fffe042ace0)
   *     example.c:50 (100000.000000 != 99999.000000)
   *     example.c:51 (100000.000000 != 99999.000000)
   *     example.c:52 (100000.000000 != 99999.000000)
   *     example.c:54 ("hello mut" != "hello MUT")
   * -- pass: 17                   fail: 17                   time: 171 ms
   **/
}

mut_tests(mut_equal_example) {
  mut_equal(5, 5);
  mut_equal(5.5, 5.5);
  mut_equal("234", "5234");

  /** output:
   * mut_equal_example (Mini-Unit_Test library `mut_equal()` example):
   *     example.c:85 ("234" != "5234")
   * -- pass: 2                    fail: 1                    time: 0 ms
   **/
}

mut_tests(mut_assert_example) {
  mut_assert(2 == 2);
  mut_assert(2 != 2);

  /** output:
   * mut_assert_example (Mini-Unit-Test library `mut_assert()` example):
   *     example.c:96 (2 != 2)
   * -- pass: 1                    fail: 1                    time: 0 ms
   **/
}

int main(int argc, char* argv[]) {
  mut_run(test_mut, "test Mini-Unit-Test library");
  mut_run(mut_equal_example, "Mini-Unit_Test library `mut_equal()` example");
  mut_run(mut_assert_example, "Mini-Unit-Test library `mut_assert()` example");

  mut_results();

  /** output:
   * SOME TESTS FAILED (20/39)
   **/

  return 0;
}
