#pragma once

#include <optional>
#include <string>

#include "scrutiny/assert/eq.h"

template <>
struct AssertEq<int> {

  static std::optional<std::string> eq(int left, int right);

};



template <>
struct AssertEq<size_t> {

  static std::optional<std::string> eq(size_t left, size_t right);

};

template <>
struct AssertEq<ssize_t> {

  static std::optional<std::string> eq(ssize_t left, ssize_t right);

};