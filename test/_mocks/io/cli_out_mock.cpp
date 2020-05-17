#include "_mocks/io/cli_out_mock.h"

#include <algorithm>

void CliOutMock::println(std::string_view out) {
  _println_calls.emplace_back(out);
}

size_t CliOutMock::println_call_count() const {
  return _println_calls.size();
}

std::string_view CliOutMock::println_call(size_t offset) const {
  return _println_calls.at(offset);
}

std::vector<std::string_view> CliOutMock::println_calls() const {
  std::vector<std::string_view> copy;
  copy.reserve(_println_calls.size());
  std::transform(
    _println_calls.cbegin(),
    _println_calls.cend(),
    std::back_inserter(copy),
    [](const auto& string) { return std::string_view(string); }
  );
  return copy;
}
