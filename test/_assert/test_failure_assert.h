#pragma once

#include "scrutiny/assert/eq.h"
#include "scrutiny/runner/test_failure.h"

template <>
struct AssertEq<TestFailure> {

  static std::optional<std::string> eq(
    const TestFailure& left, const TestFailure& right
  ) {
    if (left != right) {
      std::ostringstream oss;
      oss << "_assert " << left.to_repr() << " == " << right.to_repr();
      return oss.str();
    }
    return {};
  }

};
