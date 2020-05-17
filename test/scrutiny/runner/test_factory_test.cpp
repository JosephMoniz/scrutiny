#include "scrutiny/runner/test_factory_test.h"

#include "_assert/test_failure_assert.h"

std::optional<AssertFailure> _test_factory_unary_test_mock() {
  return AssertFailure("file", "func", 3, "fail");
}

std::vector<std::string_view> test_factory_make_params_params_mock() {
  return {"one", "two"};
}

std::optional<AssertFailure> test_factory_make_params_test_mock(
  const std::string_view& param
) {
  return AssertFailure("file", "func", 3, std::string(param));
}

std::optional<AssertFailure> test_factory_unary_test() {
  // Given ...
  //
  TestFactory factory(TestNameFactory::create("/"));

  // When ...
  //
  const auto result = factory.unary(
    "/file", "func", _test_factory_unary_test_mock
  );

  // Then ...
  //
  ASSERT_EQ(result.size(), 1);
  ASSERT_EQ(
    result.at(0)(),
    TestFailure("file::func", AssertFailure("file", "func", 3, "fail"))
  );
  return {};
}

std::optional<AssertFailure> test_factory_parameterized_test() {
  // Given ...
  //
  TestFactory factory(TestNameFactory::create("/"));

  // When ...
  //
  const auto result = factory.parameterized(
    "/file",
    "func",
    test_factory_make_params_params_mock,
    test_factory_make_params_test_mock
  );

  // Then ...
  //
  ASSERT_EQ(result.size(), 2);
  ASSERT_EQ(
    result.at(0)(),
    TestFailure("file::func-0", AssertFailure("file", "func", 3, "one"))
  );
  ASSERT_EQ(
    result.at(1)(),
    TestFailure("file::func-1", AssertFailure("file", "func", 3, "two"))
  );
  return {};
}

Test::Group test_factory_tests(const TestFactory& factory) {
  return {
    TEST(factory, test_factory_unary_test),
    TEST(factory, test_factory_parameterized_test)
  };
}
