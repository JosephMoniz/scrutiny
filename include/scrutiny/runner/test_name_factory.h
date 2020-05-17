#pragma once

#include <cstdlib>
#include <string>
#include <string_view>

class TestNameFactory final {

  size_t _file_offset;

public:

  explicit TestNameFactory(size_t file_offset);

  static TestNameFactory create(std::string_view file);

  [[nodiscard]]
  std::string unary(
    const char* file_name,
    const char* func_name
  ) const;

  [[nodiscard]]
  std::string parameterized(
    const char* file_name,
    const char* func_name,
    size_t test_number
  ) const;

};
