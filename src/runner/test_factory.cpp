#include "scrutiny/runner/test_factory.h"

#include <sstream>

TestFactory::TestFactory(size_t file_offset) :
  _file_offset(file_offset) { }

std::vector<Test>
TestFactory::make_unary_test(
  const char* file_name,
  const char* func_name,
  std::optional<AssertFailure> (* test_func)()
) const {
  std::vector<Test> tests;
  std::ostringstream oss;
  oss << &file_name[_file_offset] << "::" << func_name;
  tests.emplace_back(oss.str(), test_func);
  return tests;
}
