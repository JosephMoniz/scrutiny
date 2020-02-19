#include "scrutiny/assert/eq_test.h"

struct AssertEqNotImplementedMock {};

std::optional<AssertFailure> assert_eq_not_implemented_test() {
  // Given ...
  //
  AssertEqNotImplementedMock left;
  AssertEqNotImplementedMock right;

  // When ...
  //
  const auto result = AssertEq<AssertEqNotImplementedMock>::eq(left, right);

  // Then ...
  //
  ASSERT_EQ(result, "AssertEq<T>::eq() not implemented");
  return {};
}

Test::Group assert_eq_tests(const TestFactory& factory) {
  return {
    TEST(factory, assert_eq_not_implemented_test)
  };
}
