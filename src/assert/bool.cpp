#include "scrutiny/assert/bool.h"

#include <sstream>

std::optional<std::string> AssertEq<bool>::eq(bool left, bool right) {
  if (left != right) {
    std::ostringstream oss;
    const auto left_str = (left ? "true" : "false");
    const auto right_str = (right ? "true" : "false");
    oss << "assert " << left_str << " == " << right_str;
    return oss.str();
  }
  return {};
}