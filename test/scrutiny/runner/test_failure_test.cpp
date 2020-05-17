#include "scrutiny/runner/test_failure_test.h"


TestFailureEqualsParams::TestFailureEqualsParams(
  TestFailure&& _left,
  TestFailure&& _right,
  bool _expected_result
) :
  left(std::move(_left)),
  right(std::move(_right)),
  expected_result(_expected_result) { }

std::vector<TestFailureEqualsParams> test_failure_equals_params() {
  return {
    {
      TestFailure("left", AssertFailure("file", "func", 3, "fail")),
      TestFailure("right", AssertFailure("file", "func", 3, "fail")),
      false
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("different", "func", 3, "fail")),
      false
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("file", "different", 3, "fail")),
      false
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("file", "func", 4, "fail")),
      false
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("file", "func", 3, "different")),
      false
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      true
    }
  };
}

std::optional<AssertFailure> test_failure_equals_test(
  const TestFailureEqualsParams& params
) {
  // Given ...
  //
  const auto& left = params.left;
  const auto& right = params.right;
  const auto expected_result = params.expected_result;

  // When ...
  //
  const auto result = left == right;

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

TestFailureNotEqualsParams::TestFailureNotEqualsParams(
  TestFailure&& _left,
  TestFailure&& _right,
  bool _expected_result
) :
  left(std::move(_left)),
  right(std::move(_right)),
  expected_result(_expected_result) { }

std::vector<TestFailureNotEqualsParams> test_failure_not_equals_params() {
  return {
    {
      TestFailure("left", AssertFailure("file", "func", 3, "fail")),
      TestFailure("right", AssertFailure("file", "func", 3, "fail")),
      true
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("different", "func", 3, "fail")),
      true
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("file", "different", 3, "fail")),
      true
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("file", "func", 4, "fail")),
      true
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("file", "func", 3, "different")),
      true
    },
    {
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      TestFailure("same", AssertFailure("file", "func", 3, "fail")),
      false
    }
  };
}

std::optional<AssertFailure> test_failure_not_equals_test(
  const TestFailureNotEqualsParams& params
) {
  // Given ...
  //
  const auto& left = params.left;
  const auto& right = params.right;
  const auto expected_result = params.expected_result;

  // When ...
  //
  const auto result = left != right;

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}


std::optional<AssertFailure> test_failure_test_name_test() {
  // Given ...
  //
  TestFailure test("test", AssertFailure("file", "func", 3, "fail"));

  // When ...
  //
  const auto result = test.test_name();

  // Then ...
  //
  ASSERT_EQ(result, "test");
  return {};
}

std::optional<AssertFailure> test_failure_to_repr_test() {
  // Given ...
  //
  TestFailure failure("test", AssertFailure("file", "func", 42, "failed"));

  // When ...
  //
  const auto result = failure.to_repr();

  // Then ...
  //
  ASSERT_EQ(result, "TestFailure(test, AssertFailure(file, func, 42, failed))");
  return {};
}

std::optional<AssertFailure> test_failure_to_string_test() {
  // Given ...
  //
  TestFailure failure("test", AssertFailure("file", "func", 42, "failed"));

  // When ...
  //
  const auto result = failure.to_string();

  // Then ...
  //
  ASSERT_EQ(result, "\n---[test]\nsource: file:42\nfailed\n");
  return {};
}

Test::Group test_failure_tests(const TestFactory& factory) {
  return {
    PARAMETERIZED_TEST(
      factory,
      test_failure_equals_params,
      test_failure_equals_test
    ),
    PARAMETERIZED_TEST(
      factory,
      test_failure_not_equals_params,
      test_failure_not_equals_test
    ),
    TEST(factory, test_failure_test_name_test),
    TEST(factory, test_failure_to_repr_test),
    TEST(factory, test_failure_to_string_test)
  };
}
