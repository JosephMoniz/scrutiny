#pragma once

#include <cstdlib>
#include <vector>

#include "scrutiny/runner/test_state_message.h"
#include "scrutiny/runner/test_failure.h"
#include "scrutiny/runner/test_reporter_message.h"

class TestState final {

  size_t _total_test_count;

  size_t _completed_test_count;

  size_t _passed_test_count;

  size_t _failed_test_count;

  std::vector<TestFailure> _failures;

  [[nodiscard]]
  int _get_pct_compete() const;

  [[nodiscard]]
  TestReporterMessage::Type _visit_message(
    const TestStateMessage::Count& message
  );

  [[nodiscard]]
  TestReporterMessage::Type _visit_message(
    const TestStateMessage::Passed& message
  );

  [[nodiscard]]
  TestReporterMessage::Type _visit_message(
    const TestStateMessage::Failed& message
  );

  [[nodiscard]]
  TestReporterMessage::Type _visit_message(
    const TestStateMessage::Completed& message
  );

public:

  TestState();

  [[nodiscard]]
  size_t failure_count() const;

  [[nodiscard]]
  TestReporterMessage::Type handle(const TestStateMessage::Type& message);

};
