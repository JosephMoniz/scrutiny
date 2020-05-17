#include "scrutiny/runner/test_state_message.h"

#include <utility>

TestStateMessage::Count::Count(size_t _count) :
  count(_count) { }

TestStateMessage::Passed::Passed(std::string_view _test_name) :
  test_name(_test_name) { }

TestStateMessage::Failed::Failed(TestFailure _failure) :
  failure(std::move(_failure)) { }

TestStateMessage::Completed::Completed() = default;

TestStateMessage::Type TestStateMessage::count(size_t count) {
  return Count(count);
}

TestStateMessage::Type TestStateMessage::passed(std::string_view test_name) {
  return Passed(test_name);
}

TestStateMessage::Type TestStateMessage::failed(const TestFailure& failure) {
  return Failed(failure);
}

TestStateMessage::Type TestStateMessage::completed() {
  return Completed();
}
