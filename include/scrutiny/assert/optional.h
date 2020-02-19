#pragma once

#include <optional>
#include <string>
#include <sstream>

#include "scrutiny/assert/eq.h"

template <typename T>
class AssertEq<std::optional<T>> {

  static std::string _to_string(const std::optional<T>& optional) {
    if (optional) {
      std::ostringstream oss;
      oss << "{" << optional.value() << "}";
      return oss.str();
    } else {
      return "{}";
    }
  }

  public:

  static std::optional<std::string> eq(
    const std::optional<T>& left,
    const std::optional<T>& right
  ) {
    if (left != right) {
      std::ostringstream oss;
      oss << "assert " << _to_string(left) << " == " << _to_string(right);
      return oss.str();
    }
    return {};
  }

};
