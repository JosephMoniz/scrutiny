#include "scrutiny/assert/numeric.h"

#include <sstream>

std::optional<std::string> AssertEq<int>::eq(int left, int right) {
  if (left != right) {
    std::ostringstream oss;
    oss << "assert " << left << " == " << right;
    return oss.str();
  }
  return {};
}

std::optional<std::string> AssertEq<size_t>::eq(size_t left, size_t right) {
  if (left != right) {
    std::ostringstream oss;
    oss << "assert " << left << " == " << right;
    return oss.str();
  }
  return {};
}

std::optional<std::string> AssertEq<ssize_t>::eq(ssize_t left, ssize_t right) {
  if (left != right) {
    std::ostringstream oss;
    oss << "assert " << left << " == " << right;
    return oss.str();
  }
  return {};
}
