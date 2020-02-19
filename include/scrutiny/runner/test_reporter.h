#pragma once

#include <cstdlib>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "scrutiny/io/cli_out.h"
#include "scrutiny/runner/test_failure.h"

class TestReporter final {

  size_t _total_test_count;

  size_t _completed_test_count;

  size_t _passed_test_count;

  size_t _failed_test_count;

  std::vector<TestFailure> _failures;

  CliOut& _cli_out;

  [[nodiscard]]
  std::string _get_pct_compete() const;

public:

  class TestCount {
    size_t _count;
  public:
    explicit TestCount(size_t count);
    void operator()(TestReporter& reporter);
  };

  class TestPassed {
    std::string_view _test_name;
  public:
    explicit TestPassed(std::string_view test_name);
    void operator()(TestReporter& reporter);
  };

  class TestFailed {
    TestFailure _failure;
  public:
    explicit TestFailed(TestFailure&& failure);
    void operator()(TestReporter& reporter);
  };

  class TestsCompleted {
  public:
    TestsCompleted();
    void operator()(TestReporter& reporter);
  };

  using Message = std::variant<
    TestCount,
    TestPassed,
    TestFailed,
    TestsCompleted
  >;

  explicit TestReporter(CliOut& cli_out);

  [[nodiscard]]
  size_t failure_count() const;

  void handle(Message&& message);

};
