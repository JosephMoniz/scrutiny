#pragma once

#include <functional>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "scrutiny/assert/assert_failure.h"
#include "scrutiny/runner/test_reporter.h"

#define TEST(FACTORY, TEST) \
  FACTORY.unary(__FILE__, #TEST, TEST)

#define PARAMETERIZED_TEST(FACTORY, PARAMS, TEST) \
  FACTORY.parameterized(__FILE__, #TEST, PARAMS, TEST)


class Test final {

  using Func = std::function<std::optional<AssertFailure>()>;

  std::string _test_name;

  Func _test_func;

public:

  using Group = std::vector<std::vector<Test>>;

  using Result = std::optional<AssertFailure>;

  Test(std::string&& test_name, Func&& test_func);

  [[nodiscard]]
  std::string_view name() const;

  [[nodiscard]]
  std::optional<TestFailure> operator()() const;

};
