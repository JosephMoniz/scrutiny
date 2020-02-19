#pragma once

#include <any>
#include <optional>
#include <vector>

#include "scrutiny.h"

struct TestReporterHandleParams {
  std::vector<TestReporter::Message> messages;
  size_t expected_failure_count;
  std::vector<std::string_view> expected_output;
  TestReporterHandleParams(
    std::vector<TestReporter::Message>&& _messages,
    size_t _expected_failure_count,
    std::vector<std::string_view>&& _expected_output
  );
};

std::vector<TestReporterHandleParams> test_reporter_handle_params();

std::optional<AssertFailure> test_reporter_handle_test(
  const TestReporterHandleParams& params
);

Test::Group test_reporter_tests(const TestFactory& factory);
