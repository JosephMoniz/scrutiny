#include "scrutiny/runner/test_failure.h"

#include <sstream>

TestFailure::TestFailure(std::string_view test_name, AssertFailure&& assert) :
  _test_name(test_name),
  _assert(std::move(assert)) { }

bool TestFailure::operator==(const TestFailure& other) const {
  return (
    _test_name == other._test_name &&
    _assert == other._assert
  );
}

bool TestFailure::operator!=(const TestFailure& other) const {
  return !(*this == other);
}

std::string_view TestFailure::test_name() const {
  return _test_name;
}

std::string TestFailure::to_repr() const {
  std::ostringstream oss;
  oss << "TestFailure(" << _test_name << ", " << _assert.to_repr() << ")";
  return oss.str();
}

std::string TestFailure::to_string() const {
  std::ostringstream oss;
  oss << "\n---[" << _test_name << "]\n" << _assert.to_string();
  return oss.str();
}

std::ostream& operator<<(std::ostream& os, const TestFailure& failure) {
  return os << failure.to_repr();
}
