#include "scrutiny/assert/optional_test.h"

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
