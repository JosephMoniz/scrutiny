#include "scrutiny/assert/str.h"

#include <sstream>

std::optional<std::string> AssertEq<std::string_view>::eq(
  std::string_view left,
  std::string_view right
) {
  if (left != right) {
    std::ostringstream oss;
    oss << "assert " << left << " == " << right;
    return oss.str();
  }
  return {};
}

std::optional<std::string> AssertEq<std::string>::eq(
  const std::string& left,
  std::string_view right
) {
  return assert_eq(std::string_view(left), right);
}

std::optional<std::string> AssertEq<const char*>::eq(
  const char* left,
  std::string_view right
) {
  return assert_eq(std::string_view(left), right);
}