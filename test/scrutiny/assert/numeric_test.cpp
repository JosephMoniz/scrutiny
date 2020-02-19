#include "scrutiny/assert/numeric_test.h"

IntAssertEqParams::IntAssertEqParams(
  int _left,
  int _right,
  std::optional<std::string>&& _expected_result
) :
  left(_left),
  right(_right),
  expected_result(std::move(_expected_result)) { }

std::vector<IntAssertEqParams> int_assert_eq_params() {
  return {
    IntAssertEqParams(1, 1, {}),
    IntAssertEqParams(2, 2, {}),
    IntAssertEqParams(1, 2, "assert 1 == 2"),
    IntAssertEqParams(2, 1, "assert 2 == 1"),
  };
}

std::optional<AssertFailure> int_assert_eq_test(
  const IntAssertEqParams& params
) {
  // Given ...
  //
  const auto left = params.left;
  const auto right = params.right;
  const auto& expected_result = params.expected_result;

  // When ...
  //
  const auto result = AssertEq<int>::eq(left, right);

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

SizeTAssertEqParams::SizeTAssertEqParams(
  size_t _left,
  size_t _right,
  std::optional<std::string>&& _expected_result
) :
  left(_left),
  right(_right),
  expected_result(std::move(_expected_result)) { }

std::vector<SizeTAssertEqParams> size_t_assert_eq_params() {
  return {
    SizeTAssertEqParams(1, 1, {}),
    SizeTAssertEqParams(2, 2, {}),
    SizeTAssertEqParams(1, 2, "assert 1 == 2"),
    SizeTAssertEqParams(2, 1, "assert 2 == 1"),
  };
}

std::optional<AssertFailure> size_t_assert_eq_test(
  const SizeTAssertEqParams& params
) {
  // Given ...
  //
  const auto left = params.left;
  const auto right = params.right;
  const auto& expected_result = params.expected_result;

  // When ...
  //
  const auto result = AssertEq<size_t>::eq(left, right);

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

Test::Group numeric_assert_eq_tests(const TestFactory& factory) {
  return {
    PARAMETERIZED_TEST(factory, int_assert_eq_params, int_assert_eq_test),
    PARAMETERIZED_TEST(factory, size_t_assert_eq_params, size_t_assert_eq_test)
  };
}
