#pragma once

#include <any>

#include "scrutiny.h"

struct AssertFailureEqualsParams {
  AssertFailure left;
  AssertFailure right;
  bool expected_result;
  AssertFailureEqualsParams(
    AssertFailure&& _left,
    AssertFailure&& _right,
    bool _expected_result
  );
};

std::vector<AssertFailureEqualsParams> assert_failure_equals_params();

std::optional<AssertFailure> assert_failure_equals_test(
  const AssertFailureEqualsParams& params
);

struct AssertFailureNotEqualsParams {
  AssertFailure left;
  AssertFailure right;
  bool expected_result;
  AssertFailureNotEqualsParams(
    AssertFailure&& _left,
    AssertFailure&& _right,
    bool _expected_result
  );
};

std::vector<AssertFailureNotEqualsParams> assert_failure_not_equals_params();

std::optional<AssertFailure> assert_failure_not_equals_test(
  const AssertFailureNotEqualsParams& params
);

std::optional<AssertFailure> assert_failure_to_repr_test();

std::optional<AssertFailure> assert_failure_to_str_test();

Test::Group assert_failure_tests(const TestFactory& factory);
