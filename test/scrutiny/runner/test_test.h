#pragma once

#include "scrutiny.h"

std::optional<AssertFailure> test_name_test();

struct TestRunParams {
  Test test;
  std::optional<TestFailure> expected_result;
  TestRunParams(Test&& _test, std::optional<TestFailure>&& _expected_result);
};

std::vector<TestRunParams> test_run_params();

std::optional<AssertFailure> test_run_test(const TestRunParams& params);

Test::Group test_tests(const TestFactory& factory);
