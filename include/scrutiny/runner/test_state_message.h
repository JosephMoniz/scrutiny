#pragma once

#include <cstdlib>
#include <string_view>
#include <variant>

#include "scrutiny/runner/test_failure.h"

class TestStateMessage final {
public:

  struct Count final {
    size_t count;
    explicit Count(size_t _count);
  };

  struct Passed final {
    std::string_view test_name;
    explicit Passed(std::string_view _test_name);
  };

  struct Failed final {
    TestFailure failure;
    explicit Failed(TestFailure _failure);
  };

  struct Completed final {
    Completed();
  };

  using Type = std::variant<
    Count,
    Passed,
    Failed,
    Completed
  >;

  static Type count(size_t count);

  static Type passed(std::string_view test_name);

  static Type failed(const TestFailure& failure);

  static Type completed();

};
