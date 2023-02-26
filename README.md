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

mut_tests(test1) {
  mut_assert('a' == 'a');
}

mut_tests(test2) {
  mut_equal(5, 5);
  mut_equal(5.5, 5.5);
  mut_equal("hello mut", "hello MUT");
}

int main(void) {
  mut_run(test1, "mut_assert(expr) example");

  mut_run(test2, "mut_equal(result, expr) example");

  mut_results();

  return 0;
}
```

That produces the following output:
```text
test1 (mut_assert(expr) example):
-- pass: 0                    fail: 0                    time: 0 ms

test2 (mut_equal(result, expr) example):
    readme.c:10 ("hello mut" != "hello MUT")
-- pass: 2                    fail: 1                    time: 0 ms

ALL TESTS PASSED (2/3)
```

## Hints
     All functions/variables start with the string 'mut_'.
