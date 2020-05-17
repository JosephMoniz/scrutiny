#pragma once

#include <any>
#include <optional>
#include <vector>

#include "scrutiny.h"

struct TestSuiteRunParams {
  const char* file;
  std::function<Test::Group(const TestFactory&)> test_generator;
  int expected_result;
  std::vector<std::string_view> expected_output;
  TestSuiteRunParams(
    const char* _file,
    std::function<Test::Group(const TestFactory&)> _test_generator,
    int _expected_result,
    std::vector<std::string_view>&& _expected_output
  );
};

std::vector<TestSuiteRunParams> test_suite_run_params();

std::optional<AssertFailure> test_suite_run_test(
  const TestSuiteRunParams& params
);

Test::Group test_suite_tests(const TestFactory& factory);
