#pragma once

#include <string>
#include <vector>

#include "scrutiny/io/cli_out.h"

class CliOutMock final : public CliOut {

  std::vector<std::string> _println_calls;

public:

  void println(std::string_view out) override;

  [[nodiscard]]
  size_t println_call_count() const;

  [[nodiscard]]
  std::string_view println_call(size_t offset) const;

  [[nodiscard]]
  std::vector<std::string_view> println_calls() const;

};
