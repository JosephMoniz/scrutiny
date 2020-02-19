#pragma once

#include <functional>
#include <string>
#include <sstream>
#include <optional>
#include <vector>

#include "scrutiny/runner/test.h"

class TestFactory final {

  size_t _file_offset;

public:

  using Generator = std::function<Test::Group(const TestFactory&)>;

  explicit TestFactory(size_t file_offset);

  std::vector<Test> make_unary_test(
    const char* file_name,
    const char* func_name,
    std::optional<AssertFailure> (*test_func)()
  ) const;

  template <typename ParamFactory, typename TestFunc>
  std::vector<Test> make_parameterized_tests(
    const char* file_name,
    const char* func_name,
    ParamFactory param_factory,
    TestFunc test_func
  ) const {
    std::vector<Test> tests;
    auto params = param_factory();
    std::ostringstream oss;
    oss << &file_name[_file_offset] << "::" << func_name << "-";
    const auto name_prefix = oss.str();
    tests.reserve(params.size());
    for (auto i = 0; i < params.size(); i++) {
      auto& param = params.at(i);
      tests.emplace_back(
        name_prefix + std::to_string(i),
        [=, param = std::move(param)]() {
          return test_func(param);
        }
      );
    }
    return tests;
  }

};
