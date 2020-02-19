#pragma once

#include <string>
#include <optional>

class AssertFailure {

  std::string_view _file;

  std::string_view _func;

  int _line;

  std::string _message;

public:

  AssertFailure(
    std::string_view file,
    std::string_view func,
    int line,
    std::string&& message
  );

  bool operator==(const AssertFailure& other) const;

  bool operator!=(const AssertFailure& other) const;

  [[nodiscard]]
  std::string to_repr() const;

  [[nodiscard]]
  std::string to_string() const;

};
