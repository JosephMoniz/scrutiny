#include "scrutiny/runner/test_reporter_message.h"

#include <utility>

TestReporterMessage::Count::Count(int _count) :
  count(_count) { }

TestReporterMessage::Passed::Passed(
  int _progress,
  std::string_view _test_name
) :
  progress(_progress),
  test_name(_test_name) { }

TestReporterMessage::Failed::Failed(
  int _progress,
  TestFailure _failure
) :
  progress(_progress),
  failure(std::move(_failure)) { }

TestReporterMessage::Completed::Completed(
  size_t _completed_test_count,
  size_t _failed_test_count,
  size_t _passed_test_count,
  std::vector<TestFailure>  _failures
) :
  completed_test_count(_completed_test_count),
  failed_test_count(_failed_test_count),
  passed_test_count(_passed_test_count),
  failures(std::move(_failures)) { }

TestReporterMessage::Type TestReporterMessage::count(int count) {
  return Count(count);
}

TestReporterMessage::Type TestReporterMessage::passed(
  int progress,
  std::string_view test_name
) {
  return Passed(progress, test_name);
}

TestReporterMessage::Type TestReporterMessage::failed(
  int progress, const TestFailure& failure
) {
  return Failed(progress, failure);
}

TestReporterMessage::Type TestReporterMessage::completed(
  size_t completed_test_count,
  size_t failed_test_count,
  size_t passed_test_count,
  const std::vector<TestFailure>& failures
) {
  return Completed(
    completed_test_count,
    failed_test_count,
    passed_test_count,
    failures
  );
}
