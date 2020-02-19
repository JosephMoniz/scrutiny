#pragma once

#include <string>
#include <string_view>
#include <iostream>

#include "scrutiny/assert/assert_failure.h"

class TestFailure final {

  std::string _test_name;

  AssertFailure _assert;

public:

  TestFailure(std::string_view test_name, AssertFailure&& assert);

  bool operator==(const TestFailure& other) const;

  bool operator!=(const TestFailure& other) const;

  [[nodiscard]]
  std::string_view test_name() const;

  [[nodiscard]]
  std::string to_repr() const;

  [[nodiscard]]
  std::string to_string() const;

};

std::ostream &operator<<(std::ostream &os, const TestFailure& failure);