#include "scrutiny/assert/vector_test.h"

VectorAssertEqParams::VectorAssertEqParams(
  std::vector<int>&& _left,
  std::vector<int>&& _right,
  std::optional<std::string>&& _expected_result
) :
  left(std::move(_left)),
  right(std::move(_right)),
  expected_result(std::move(_expected_result)) { }

std::vector<VectorAssertEqParams> vector_assert_eq_params() {
  return {
    VectorAssertEqParams({1}, {1}, {}),
    VectorAssertEqParams({2}, {2}, {}),
    VectorAssertEqParams({1, 2}, {1, 2}, {}),
    VectorAssertEqParams({}, {}, {}),
    VectorAssertEqParams({1}, {2}, "assert {1} == {2}"),
    VectorAssertEqParams({2}, {1}, "assert {2} == {1}"),
    VectorAssertEqParams({1}, {}, "assert {1} == {}"),
    VectorAssertEqParams({}, {1}, "assert {} == {1}"),
    VectorAssertEqParams({1, 2}, {1}, "assert {1,2} == {1}"),
    VectorAssertEqParams({1}, {1, 2}, "assert {1} == {1,2}"),
    VectorAssertEqParams({1, 2}, {1, 3}, "assert {1,2} == {1,3}"),
    VectorAssertEqParams({1, 3}, {1, 2}, "assert {1,3} == {1,2}"),
  };
}

std::optional<AssertFailure> vector_assert_eq_test(
  const VectorAssertEqParams& params
) {
  // Given ...
  //
  const auto left = params.left;
  const auto right = params.right;
  const auto& expected_result = params.expected_result;

  // When ...
  //
  const auto result = AssertEq<std::vector<int>>::eq(left, right);

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

Test::Group vector_assert_eq_tests(const TestFactory& factory) {
  return {
    PARAMETERIZED_TEST(
      factory,
      vector_assert_eq_params,
      vector_assert_eq_test
    )
  };
}
