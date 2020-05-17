#pragma once

#include "scrutiny.h"

struct StringViewAssertEqParams {
  std::string left;
  std::string right;
  std::optional<std::string> expected_result;
  StringViewAssertEqParams(
    std::string&& _left,
    std::string&& _right,
    std::optional<std::string>&& _expected_result
  );
};

std::vector<StringViewAssertEqParams> string_view_assert_eq_params();

std::optional<AssertFailure> string_view_assert_eq_test(
  const StringViewAssertEqParams& params
);

struct StringAssertEqParams {
  std::string left;
  std::string right;
  std::optional<std::string> expected_result;
  StringAssertEqParams(
    std::string&& _left,
    std::string&& _right,
    std::optional<std::string>&& _expected_result
  );
};

std::vector<StringAssertEqParams> string_assert_eq_params();

std::optional<AssertFailure> string_assert_eq_test(
  const StringAssertEqParams& params
);

struct CStringAssertEqParams {
  const char* left;
  const char* right;
  std::optional<std::string> expected_result;
  CStringAssertEqParams(
    const char* _left,
    const char* _right,
    std::optional<std::string>&& _expected_result
  );
};

std::vector<CStringAssertEqParams> c_string_assert_eq_params();

std::optional<AssertFailure> c_string_assert_eq_test(
  const CStringAssertEqParams& params
);

Test::Group str_assert_eq_tests(const TestFactory& factory);
