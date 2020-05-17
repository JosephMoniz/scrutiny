#include "scrutiny/assert/pointer.h"

#include <sstream>

std::optional<std::string> AssertEq<void*>::eq(void* left, void* right) {
  if (left != right) {
    std::ostringstream oss;
    oss << "assert " << left << " == " << right;
    return oss.str();
  }
  return {};
}