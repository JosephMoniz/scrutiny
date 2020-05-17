#pragma once

#include "scrutiny.h"

struct BoolAssertEqParams {
  bool left;
  bool right;
  std::optional<std::string> expected_result;
  BoolAssertEqParams(
    bool _left,
    bool _right,
    std::optional<std::string>&& _expected_result
  );
};

std::vector<BoolAssertEqParams> bool_assert_eq_params();

std::optional<AssertFailure> bool_assert_eq_test(
  const BoolAssertEqParams& params
);

Test::Group bool_assert_eq_tests(const TestFactory& factory);
