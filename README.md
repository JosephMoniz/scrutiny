# Scrutiny

A C++17 test framework that supports type safe parameterized tests

## Examples

Unary Test Examples:
```c++
std::optional<AssertFailure> test_failure_to_repr_test() {
  // Given ...
  //
  TestFailure failure("test", AssertFailure("file", "func", 42, "failed"));

  // When ...
  //
  const auto result = failure.to_repr();

  // Then ...
  //
  ASSERT_EQ(result, "TestFailure(test, AssertFailure(file, func, 42, failed))");
  return {};
}

std::optional<AssertFailure> test_failure_to_string_test() {
  // Given ...
  //
  TestFailure failure("test", AssertFailure("file", "func", 42, "failed"));

  // When ...
  //
  const auto result = failure.to_string();

  // Then ...
  //
  ASSERT_EQ(result, "\n---[test]\nsource: file:42\nfailed\n");
  return {};
}

Test::Group test_failure_tests(const TestFactory& factory) {
  return {
    TEST(factory, test_failure_to_repr_test),
    TEST(factory, test_failure_to_string_test)
  };
}

```

Parameterized Test Example:
```c++
OptionalAssertEqParams::OptionalAssertEqParams(
  std::optional<int> _left,
  std::optional<int> _right,
  std::optional<std::string>&& _expected_result
) :
  left(_left),
  right(_right),
  expected_result(std::move(_expected_result)) { }


std::vector<OptionalAssertEqParams> optional_assert_eq_params() {
  return {
    OptionalAssertEqParams(1, 1, {}),
    OptionalAssertEqParams(2, 2, {}),
    OptionalAssertEqParams({}, {}, {}),
    OptionalAssertEqParams(1, 2, "assert {1} == {2}"),
    OptionalAssertEqParams(2, 1, "assert {2} == {1}"),
    OptionalAssertEqParams(1, {}, "assert {1} == {}"),
    OptionalAssertEqParams({}, 1, "assert {} == {1}"),
  };
}

std::optional<AssertFailure> optional_assert_eq_test(
  const OptionalAssertEqParams& params
) {
  // Given ...
  //
  const auto left = params.left;
  const auto right = params.right;
  const auto& expected_result = params.expected_result;

  // When ...
  //
  const auto result = AssertEq<std::optional<int>>::eq(left, right);

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

Test::Group optional_assert_eq_tests(const TestFactory& factory) {
  return {
    PARAMETERIZED_TEST(
      factory,
      optional_assert_eq_params,
      optional_assert_eq_test
    )
  };
}
```

## Building

Scrutiny is built as static library. To compile it you will need a recent
version of CMake and a C++ compiler that supports C++17 or greater.

First, construct the make file via cmake:
```bash
cmake .
```

Then run the makefile to produce the `libscrutiny.a` artifact:
```bash
make
```

## Contributing

Scrutiny is self hosted, which is to say that scrutiny tests itself. To run
the tests follow the instructions in the `Building` section above and then
execute the test artifact.

```bash
./scrutiny_tests
```

All PRs must be accompanied by the appropriate test changes and have adequate 
test coverage for all changes.