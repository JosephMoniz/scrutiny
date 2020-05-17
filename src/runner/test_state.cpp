#include "scrutiny/runner/test_state.h"

int TestState::_get_pct_compete() const {
  float completed = _completed_test_count;
  float total = _total_test_count;
  float percent = (completed / total) * 100;
  int truncated_percent = (int) percent;
  return truncated_percent;
}

TestReporterMessage::Type TestState::_visit_message(
  const TestStateMessage::Count& message
) {
  _total_test_count = message.count;
  return TestReporterMessage::count(_total_test_count);
}

TestReporterMessage::Type TestState::_visit_message(
  const TestStateMessage::Passed& message
) {
  _passed_test_count++;
  _completed_test_count++;
  const auto progress = _get_pct_compete();
  return TestReporterMessage::passed(progress, message.test_name);
}

TestReporterMessage::Type TestState::_visit_message(
  const TestStateMessage::Failed& message
) {
  _failed_test_count++;
  _completed_test_count++;
  const auto progress = _get_pct_compete();
  _failures.push_back(message.failure);
  return TestReporterMessage::failed(progress, message.failure);
}

TestReporterMessage::Type TestState::_visit_message(
  const TestStateMessage::Completed& message
) {
  return TestReporterMessage::completed(
    _completed_test_count,
    _failed_test_count,
    _passed_test_count,
    _failures
  );
}

TestState::TestState() :
  _total_test_count(0),
  _completed_test_count(0),
  _passed_test_count(0),
  _failed_test_count(0),
  _failures() { }

size_t TestState::failure_count() const {
  return _failed_test_count;
}

TestReporterMessage::Type TestState::handle(
  const TestStateMessage::Type& message
) {
  const auto visitor = [this](const auto& self) -> TestReporterMessage::Type {
    return _visit_message(self);
  };
  return std::visit(visitor, message);
}
