#pragma once

#include <sstream>

#include "scrutiny/assert/assert_failure.h"
#include "scrutiny/assert/eq.h"

template <>
struct AssertEq<AssertFailure> {

  static std::optional<std::string> eq(
    const AssertFailure& left, const AssertFailure& right
  ) {
    if (left != right) {
      std::ostringstream oss;
      oss << "_assert " << left.to_repr() << " == " << right.to_repr();
      return oss.str();
    }
    return {};
  }

};
