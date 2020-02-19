#include "scrutiny/runner/test.h"

Test::Test(std::string&& test_name, Test::Func&& test_func) :
  _test_name(std::move(test_name)),
  _test_func(std::move(test_func)) { }

std::string_view Test::name() const {
  return _test_name;
}

std::optional<TestFailure> Test::operator()() const {
  auto failure = _test_func();
  if (failure) {
    return TestFailure(_test_name, std::move(failure.value()));
  }
  return {};
}
