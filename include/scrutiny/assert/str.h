#pragma once

#include <optional>
#include <string_view>
#include <string>

#include "scrutiny/assert/eq.h"

template <>
struct AssertEq<std::string_view> {

  static std::optional<std::string> eq(
    std::string_view left,
    std::string_view right
  );

};

template <>
struct AssertEq<std::string> {

  static std::optional<std::string> eq(
    const std::string& left,
    std::string_view right
  );

};

template <>
struct AssertEq<const char*> {

  static std::optional<std::string> eq(
    const char* left,
    std::string_view right
  );

};
