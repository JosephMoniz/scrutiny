#pragma once

#include <initializer_list>
#include <optional>

#include "scrutiny/assert/assert_failure.h"

#define ASSERT_EQ(TEST, EXPECTED) do { \
  auto __message = assert_eq(TEST, EXPECTED); \
  if (__message) { \
    return std::make_optional<AssertFailure>( \
      __FILE__, \
      __func__, \
      __LINE__, \
      std::move(__message.value()) \
    ); \
  } \
} while (0)

template <typename T>
struct AssertEq {

  template <typename U>
  static std::optional<std::string> eq(const T left, const U right) {
    return "AssertEq<T>::eq() not implemented";
  }

};

template <
  typename T,
  typename U,
  class = std::enable_if_t<std::is_class_v<T>>,
  class = std::enable_if_t<std::is_class_v<U>>
>
std::optional<std::string> assert_eq(const T& left, const U& right) {
  return AssertEq<T>::eq(left, right);
}

template <
  typename T,
  typename U,
  class = std::enable_if_t<std::is_class_v<T>>,
  class = std::enable_if_t<std::is_fundamental_v<U> || std::is_scalar_v<U>>
>
std::optional<std::string> assert_eq(const T& left, const U right) {
  return AssertEq<T>::eq(left, right);
}

template <
  typename T,
  typename U,
  class = std::enable_if_t<std::is_fundamental_v<T> || std::is_scalar_v<T>>,
  class = std::enable_if_t<std::is_fundamental_v<U> || std::is_scalar_v<U>>
>
std::optional<std::string> assert_eq(const T left, const U right) {
  return AssertEq<T>::eq(left, right);
}

template <
  typename T,
  typename U,
  class = std::enable_if_t<std::is_fundamental_v<T> || std::is_scalar_v<T>>,
  class = std::enable_if_t<std::is_class_v<U>>
>
std::optional<std::string> assert_eq(const T left, const U& right) {
  return AssertEq<T>::eq(left, right);
}
