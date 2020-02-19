#pragma once

#include "scrutiny.h"

struct VectorAssertEqParams {
  std::vector<int> left;
  std::vector<int> right;
  std::optional<std::string> expected_result;
  VectorAssertEqParams(
    std::vector<int>&& _left,
    std::vector<int>&& _right,
    std::optional<std::string>&& _expected_result
  );
};

std::vector<VectorAssertEqParams> vector_assert_eq_params();

std::optional<AssertFailure> vector_assert_eq_test(
  const VectorAssertEqParams& params
);

Test::Group vector_assert_eq_tests(const TestFactory& factory);