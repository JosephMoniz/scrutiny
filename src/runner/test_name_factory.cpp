#include <scrutiny/runner/test_name_factory.h>

#include <sstream>

TestNameFactory::TestNameFactory(size_t file_offset) :
  _file_offset(file_offset) { }

TestNameFactory TestNameFactory::create(std::string_view file) {
  const auto folder_offset = file.find_last_of('/');
  if (folder_offset == std::string_view::npos) {
    return TestNameFactory(0);
  }
  const auto folder = file.substr(0, folder_offset);
  const auto parent_offset = folder.find_last_of('/');
  if (parent_offset == std::string_view::npos) {
    return TestNameFactory(folder.length() + 1);
  }
  return TestNameFactory(parent_offset + 1);
}

std::string TestNameFactory::unary(
  const char* file_name,
  const char* func_name
) const {
  std::ostringstream oss;
  oss << &file_name[_file_offset] << "::" << func_name;
  return oss.str();
}

std::string TestNameFactory::parameterized(
  const char* file_name,
  const char* func_name,
  size_t test_number
) const {
  std::ostringstream oss;
  oss << &file_name[_file_offset] << "::" << func_name << "-" << test_number;
  return oss.str();
}
