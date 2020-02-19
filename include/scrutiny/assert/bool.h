#pragma once

#include <optional>
#include <string>

#include "scrutiny/assert/eq.h"

template <>
struct AssertEq<bool> {

  static std::optional<std::string> eq(bool left, bool right);

};
