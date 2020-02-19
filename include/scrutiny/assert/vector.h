#pragma once

#include <optional>
#include <string>
#include <vector>
#include <sstream>

#include "scrutiny/assert/eq.h"

template <typename T>
class AssertEq<std::vector<T>> {

  static std::string _to_string(const std::vector<T>& vector) {
    if (vector.empty()) {
      return "{}";
    }
    std::ostringstream oss;
    const auto second_to_last = vector.cend() - 1;
    oss << "{";
    for (auto item = vector.cbegin(); item != second_to_last; item++) {
      oss << *item << ",";
    }
    oss << vector.back() << "}";
    return oss.str();
  }

  public:

  static std::optional<std::string> eq(
    const std::vector<T>& left,
    const std::vector<T>& right
  ) {
    if (left != right) {
      std::ostringstream oss;
      oss << "assert " << _to_string(left) << " == " << _to_string(right);
      return oss.str();
    }
    return {};
  }

};
