#include "scrutiny/runner/test_name_factory_test.h"

std::optional<AssertFailure> test_name_factory_unary_test() {
  // Given ...
  //
  const auto factory = TestNameFactory::create("/srv/tests/main.cpp");
  const auto file_name = "/srv/tests/runner/test.cpp";
  const auto func_name = "test_things";

  // When ...
  //
  const auto result = factory.unary(file_name, func_name);

  // Then ...
  //
  ASSERT_EQ(result, "tests/runner/test.cpp::test_things");
  return {};
}

std::optional<AssertFailure> test_name_factory_parameterized_test() {
  // Given ...
  //
  const auto factory = TestNameFactory::create("/srv/tests/main.cpp");
  const auto file_name = "/srv/tests/runner/test.cpp";
  const auto func_name = "test_things";

  // When ...
  //
  const auto result = factory.parameterized(file_name, func_name, 42);

  // Then ...
  //
  ASSERT_EQ(result, "tests/runner/test.cpp::test_things-42");
  return {};
}

Test::Group test_name_factory_tests(const TestFactory& factory) {
  return {
    TEST(factory, test_name_factory_unary_test),
    TEST(factory, test_name_factory_parameterized_test)
  };
}
