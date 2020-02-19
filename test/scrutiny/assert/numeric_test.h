#pragma once

#include "scrutiny.h"

struct IntAssertEqParams {
  int left;
  int right;
  std::optional<std::string> expected_result;
  IntAssertEqParams(
    int _left,
    int _right,
    std::optional<std::string>&& _expected_result
  );
};

std::vector<IntAssertEqParams> int_assert_eq_params();

std::optional<AssertFailure> int_assert_eq_test(
  const IntAssertEqParams& params
);

struct SizeTAssertEqParams {
  size_t left;
  size_t right;
  std::optional<std::string> expected_result;
  SizeTAssertEqParams(
    size_t _left,
    size_t _right,
    std::optional<std::string>&& _expected_result
  );
};

std::vector<SizeTAssertEqParams> size_t_assert_eq_params();

std::optional<AssertFailure> size_t_assert_eq_test(
  const SizeTAssertEqParams& params
);

Test::Group numeric_assert_eq_tests(const TestFactory& factory);
