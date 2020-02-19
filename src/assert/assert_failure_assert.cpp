#include "scrutiny/assert/assert_failure.h"

#include <sstream>

AssertFailure::AssertFailure(
  std::string_view file,
  std::string_view func,
  int line,
  std::string&& message
) :
  _file(file),
  _func(func),
  _line(line),
  _message(std::move(message)) { }

bool AssertFailure::operator==(const AssertFailure& other) const {
  return (
    _file == other._file &&
    _func == other._func &&
    _line == other._line &&
    _message == other._message
  );
}

bool AssertFailure::operator!=(const AssertFailure& other) const {
  return !(*this == other);
}

std::string AssertFailure::to_repr() const {
  std::ostringstream oss;
  auto line = std::to_string(_line);
  oss << "AssertFailure("
      << _file << ", " << _func << ", " << line << ", " << _message
      << ")";
  return oss.str();
}

std::string AssertFailure::to_string() const {
  std::ostringstream oss;
  auto line = std::to_string(_line);
  oss << "source: " << _file << ":" << line << "\n" << _message << "\n";
  return oss.str();
}
