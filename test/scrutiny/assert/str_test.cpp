#include "scrutiny/assert/str_test.h"

StringViewAssertEqParams::StringViewAssertEqParams(
  std::string&& _left,
  std::string&& _right,
  std::optional<std::string>&& _expected_result
) :
  left(std::move(_left)),
  right(std::move(_right)),
  expected_result(std::move(_expected_result)) { }

std::vector<StringViewAssertEqParams> string_view_assert_eq_params() {
  return {
    {"a", "a", {}},
    {"b", "b", {}},
    {"a", "b", "assert a == b"},
    {"b", "a", "assert b == a"}
  };
}

std::optional<AssertFailure> string_view_assert_eq_test(
  const StringViewAssertEqParams& params
) {
  // Given ...
  //
  const auto left = params.left;
  const auto right = params.right;
  const auto& expected_result = params.expected_result;

  // When ...
  //
  const auto result = AssertEq<std::string_view>::eq(left, right);

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

StringAssertEqParams::StringAssertEqParams(
  std::string&& _left,
  std::string&& _right,
  std::optional<std::string>&& _expected_result
) :
  left(std::move(_left)),
  right(std::move(_right)),
  expected_result(std::move(_expected_result)) { }


std::vector<StringAssertEqParams> string_assert_eq_params() {
  return {
    {"a", "a", {}},
    {"b", "b", {}},
    {"a", "b", "assert a == b"},
    {"b", "a", "assert b == a"}
  };
}

std::optional<AssertFailure> string_assert_eq_test(
  const StringAssertEqParams& params
) {
  // Given ...
  //
  const auto left = params.left;
  const auto right = params.right;
  const auto& expected_result = params.expected_result;

  // When ...
  //
  const auto result = AssertEq<std::string>::eq(left, right);

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

CStringAssertEqParams::CStringAssertEqParams(
  const char* _left,
  const char* _right,
  std::optional<std::string>&& _expected_result
) :
  left(_left),
  right(_right),
  expected_result(std::move(_expected_result)) { }

std::vector<CStringAssertEqParams> c_string_assert_eq_params() {
  return {
    {"a", "a", {}},
    {"b", "b", {}},
    {"a", "b", "assert a == b"},
    {"b", "a", "assert b == a"}
  };
}

std::optional<AssertFailure> c_string_assert_eq_test(
  const CStringAssertEqParams& params
) {
  // Given ...
  //
  const auto left = params.left;
  const auto right = params.right;
  const auto& expected_result = params.expected_result;

  // When ...
  //
  const auto result = AssertEq<const char*>::eq(left, right);

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

Test::Group str_assert_eq_tests(const TestFactory& factory) {
  return {
    PARAMETERIZED_TEST(
      factory,
      string_view_assert_eq_params,
      string_view_assert_eq_test
    ),
    PARAMETERIZED_TEST(
      factory,
      string_assert_eq_params,
      string_assert_eq_test
    ),
    PARAMETERIZED_TEST(
      factory,
      c_string_assert_eq_params,
      c_string_assert_eq_test
    )
  };
}
