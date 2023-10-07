/**
 * Copyright (c) 2023 by RunThem <iccy.fun@outlook.com> - All rights reserved.
 **/

#include "mut.h"

#include <string.h>

mut_test(mut_test_1) {
  mut_assert(5 != 5);
  mut_assert(5.5 != 5.5);
  mut_assert(strcmp("234", "5234"));
}

mut_test(mut_test_2) {
  mut_assert(1 == 2);
  mut_assert(2 == 2);
  mut_assert(3 != 3);
}

mut_group(mut_group_1) {
  mut_add_test(mut_test_1, "example 1");
  mut_add_test(mut_test_2, "example 2");
}

mut_test(mut_test_3) {
  mut_assert(5 != 5);
}

mut_test(mut_test_4) {
  mut_assert(NULL != 0);
}

mut_group(mut_group_2) {
  mut_add_test(mut_test_3, "example 3");
  mut_add_test(mut_test_4, "example 4");
}

mut_extern(mut_tests);

int main(int argc, char* argv[]) {
  mut_init("Mini-Unit-Test");

  mut_add_group(mut_group_1, "group 1");
  mut_add_group(mut_group_2, "group 2");

  mut_results();

  return 0;
}
