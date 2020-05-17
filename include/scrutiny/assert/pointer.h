#pragma once

#include <optional>
#include <string>

#include "scrutiny/assert/eq.h"

template <>
struct AssertEq<void*> {

  static std::optional<std::string> eq(void* left, void* right);

};
