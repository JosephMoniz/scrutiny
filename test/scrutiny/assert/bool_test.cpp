#include "scrutiny/assert/bool_test.h"

#include "scrutiny/assert/bool.h"

BoolAssertEqParams::BoolAssertEqParams(
  bool _left,
  bool _right,
  std::optional<std::string>&& _expected_result
) :
  left(_left),
  right(_right),
  expected_result(std::move(_expected_result)) { }

std::vector<BoolAssertEqParams> bool_assert_eq_params() {
  return {
    {true, true, {}},
    {false, false, {}},
    {true, false, "assert true == false"},
    {false, true, "assert false == true"}
  };
}

std::optional<AssertFailure> bool_assert_eq_test(
  const BoolAssertEqParams& params
) {
  // Given ...
  //
  const auto left = params.left;
  const auto right = params.right;
  const auto& expected_result = params.expected_result;

  // When ...
  //
  const auto result = AssertEq<bool>::eq(left, right);

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

Test::Group bool_assert_eq_tests(const TestFactory& factory) {
  return {
    PARAMETERIZED_TEST(factory, bool_assert_eq_params, bool_assert_eq_test)
  };
}

