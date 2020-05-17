#pragma once

#include <string_view>
#include <variant>
#include <vector>

#include "scrutiny/runner/test_failure.h"

class TestReporterMessage final {
public:

  struct Count final {
    int count;
    explicit Count(int _count);
  };

  struct Passed final {
    int progress;
    std::string_view test_name;
    explicit Passed(int _progress, std::string_view _test_name);
  };

  struct Failed final {
    int progress;
    TestFailure failure;
    explicit Failed(int _progress, TestFailure _failure);
  };

  struct Completed final {
    size_t completed_test_count;
    size_t failed_test_count;
    size_t passed_test_count;
    std::vector<TestFailure> failures;
    Completed(
      size_t _completed_test_count,
      size_t _failed_test_count,
      size_t _passed_test_count,
      std::vector<TestFailure>  _failures
    );
  };

  using Type = std::variant<
    Count,
    Passed,
    Failed,
    Completed
  >;

  [[nodiscard]]
  static Type count(int count);

  [[nodiscard]]
  static Type passed(int progress, std::string_view test_name);

  [[nodiscard]]
  static Type failed(int progress, const TestFailure& failure);

  [[nodiscard]]
  static Type completed(
    size_t completed_test_count,
    size_t failed_test_count,
    size_t passed_test_count,
    const std::vector<TestFailure>& failures
  );

};
