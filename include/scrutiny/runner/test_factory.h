#pragma once

#include <functional>
#include <string>
#include <optional>
#include <vector>

#include "scrutiny/runner/test.h"
#include "scrutiny/runner/test_name_factory.h"

class TestFactory final {

  TestNameFactory _test_name_factory;

public:

  using Generator = std::function<Test::Group(const TestFactory&)>;

  explicit TestFactory(TestNameFactory test_name_factory);

  std::vector<Test> unary(
    const char* file_name,
    const char* func_name,
    std::optional<AssertFailure> (*test_func)()
  ) const;

  template <typename ParamFactory, typename TestFunc>
  std::vector<Test> parameterized(
    const char* file_name,
    const char* func_name,
    ParamFactory param_factory,
    TestFunc test_func
  ) const {
    std::vector<Test> tests;
    auto params = param_factory();
    tests.reserve(params.size());
    for (auto i = 0; i < params.size(); i++) {
      auto name = _test_name_factory.parameterized(file_name, func_name, i);
      auto& param = params.at(i);
      tests.emplace_back(
        std::move(name),
        [=, param = std::move(param)]() { return test_func(param); }
      );
    }
    return tests;
  }

};
