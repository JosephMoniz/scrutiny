#pragma once

#include "scrutiny.h"

struct OptionalAssertEqParams {
  std::optional<int> left;
  std::optional<int> right;
  std::optional<std::string> expected_result;
  OptionalAssertEqParams(
    std::optional<int> _left,
    std::optional<int> _right,
    std::optional<std::string>&& _expected_result
  );
};

std::vector<OptionalAssertEqParams> optional_assert_eq_params();

std::optional<AssertFailure> optional_assert_eq_test(
  const OptionalAssertEqParams& params
);

Test::Group optional_assert_eq_tests(const TestFactory& factory);