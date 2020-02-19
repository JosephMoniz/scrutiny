#pragma once

#include <any>
#include <vector>
#include <optional>

#include "scrutiny.h"

struct TestFailureEqualsParams {
  TestFailure left;
  TestFailure right;
  bool expected_result;
  TestFailureEqualsParams(
    TestFailure&& _left,
    TestFailure&& _right,
    bool _expected_result
  );
};

std::vector<TestFailureEqualsParams> test_failure_equals_params();

std::optional<AssertFailure> test_failure_equals_test(
  const TestFailureEqualsParams& params
);

struct TestFailureNotEqualsParams {
  TestFailure left;
  TestFailure right;
  bool expected_result;
  TestFailureNotEqualsParams(
    TestFailure&& _left,
    TestFailure&& _right,
    bool _expected_result
  );
};

std::vector<TestFailureNotEqualsParams> test_failure_not_equals_params();

std::optional<AssertFailure> test_failure_not_equals_test(
  const TestFailureNotEqualsParams& params
);

std::optional<AssertFailure> test_failure_test_name_test();

std::optional<AssertFailure> test_failure_to_repr_test();

std::optional<AssertFailure> test_failure_to_string_test();

Test::Group test_failure_tests(const TestFactory& factory);
