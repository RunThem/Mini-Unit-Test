# Mini-Unit-Test(MUT)

`Mut` is a very minimal unit-testing "framework" written in ANSI C and
implemented in a single header file. It's handy when you want some real simple
unit tests for a small project.

Basically, it implements assertion and equal functions. It'll track and time
how many tests pass and fail. Failed tests will also display which line the
failing test code was on.

> fork [minctest](https://github.com/codeplea/minctest)

## Features

- **C11 with no dependencies**.
- Single header file.
- Reports file and line number for failed assertions.
- Reports run time for each test.
- Tests continue even after an assertion fails.
- Has assertion for checking float equality.
- Released under the MIT license - free for nearly any use.

## Example
```c
#include "mut.h"

mut_test(mut_assert_example) {
  mut_assert(2 == 2);
  mut_assert(2 != 2);
}

mut_group(mut_example) {
  mut_add_test(mut_assert_example, "Mini-Unit-Test library `mut_assert()` example");
}

int main(int argc, char* argv[]) {
  mut_init("Mini-Unit-Test example");

  mut_add_group(mut_example, "Mini-Unit-Test library example");

  mut_results();

  return 0;
}
```

That produces the following output:
```text
****************************************************
               Mini-Unit-Test example
****************************************************
mut_example ("Mini-Unit-Test library example"):
    mut_assert_example ("Mini-Unit-Test library `mut_assert()` example"):
        example.c:71 (2 != 2)
    -- pass: 1          fail: 1

tests passed (1/2)

****************************************************
           TESTS PASSED (1/2)
****************************************************
```

## Hints
     All functions/variables start with the string 'mut_'.
