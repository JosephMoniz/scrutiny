#include "scrutiny/runner/test_factory.h"

#include <sstream>

TestFactory::TestFactory(TestNameFactory test_name_factory) :
  _test_name_factory(test_name_factory) { }

std::vector<Test>
TestFactory::unary(
  const char* file_name,
  const char* func_name,
  std::optional<AssertFailure> (*test_func)()
) const {
  std::vector<Test> tests;
  auto name = _test_name_factory.unary(file_name, func_name);
  tests.emplace_back(std::move(name), test_func);
  return tests;
}
