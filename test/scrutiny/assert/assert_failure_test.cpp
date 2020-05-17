#include "scrutiny/assert/assert_failure_test.h"

AssertFailureEqualsParams::AssertFailureEqualsParams(
  AssertFailure&& _left, AssertFailure&& _right, bool _expected_result
) :
  left(std::move(_left)),
  right(std::move(_right)),
  expected_result(_expected_result) { }

std::vector<AssertFailureEqualsParams> assert_failure_equals_params() {
  return {
    {
      AssertFailure("test.h", "test", 42, "failed"),
      AssertFailure("test.h", "test", 42, "failed"),
      true
    },
    {
      AssertFailure("idk", "test", 42, "failed"),
      AssertFailure("test.h", "test", 42, "failed"),
      false
    },
    {
      AssertFailure("test.h", "idk", 42, "failed"),
      AssertFailure("test.h", "test", 42, "failed"),
      false
    },
    {
      AssertFailure("test.h", "test", 3, "failed"),
      AssertFailure("test.h", "test", 42, "failed"),
      false
    },
    {
      AssertFailure("test.h", "test", 42, "idk"),
      AssertFailure("test.h", "test", 42, "failed"),
      false
    }
  };
}

std::optional<AssertFailure> assert_failure_equals_test(
  const AssertFailureEqualsParams& params
) {
  // Given ...
  //
  const auto& left = params.left;
  const auto& right = params.right;
  auto expected_result = params.expected_result;

  // When ...
  //
  auto result = left == right;

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

AssertFailureNotEqualsParams::AssertFailureNotEqualsParams(
  AssertFailure&& _left, AssertFailure&& _right, bool _expected_result
) :
  left(std::move(_left)),
  right(std::move(_right)),
  expected_result(_expected_result) { }

std::vector<AssertFailureNotEqualsParams> assert_failure_not_equals_params() {
  return {
    {
      AssertFailure("test.h", "test", 42, "failed"),
      AssertFailure("test.h", "test", 42, "failed"),
      false
    },
    {
      AssertFailure("idk", "test", 42, "failed"),
      AssertFailure("test.h", "test", 42, "failed"),
      true
    },
    {
      AssertFailure("test.h", "idk", 42, "failed"),
      AssertFailure("test.h", "test", 42, "failed"),
      true
    },
    {
      AssertFailure("test.h", "test", 3, "failed"),
      AssertFailure("test.h", "test", 42, "failed"),
      true
    },
    {
      AssertFailure("test.h", "test", 42, "idk"),
      AssertFailure("test.h", "test", 42, "failed"),
      true
    }
  };
}

std::optional<AssertFailure> assert_failure_not_equals_test(
  const AssertFailureNotEqualsParams& params
) {
  // Given ...
  //
  const auto& left = params.left;
  const auto& right = params.right;
  auto expected_result = params.expected_result;

  // When ...
  //
  auto result = left != right;

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

std::optional<AssertFailure> assert_failure_to_repr_test() {
  // Given ...
  //
  AssertFailure failure("test.h", "test", 42, "failed");

  // When ...
  //
  const auto result = failure.to_repr();

  // Then ...
  //
  ASSERT_EQ(result, "AssertFailure(test.h, test, 42, failed)");
  return {};
}

std::optional<AssertFailure> assert_failure_to_str_test() {
  // Given ...
  //
  AssertFailure failure("test.h", "test", 42, "failed");

  // When ...
  //
  const auto result = failure.to_string();

  // Then ...
  //
  const char* expected_out = "source: test.h:42\nfailed\n";
  ASSERT_EQ(result, expected_out);
  return {};
}

Test::Group assert_failure_tests(const TestFactory& factory) {
  return {
    PARAMETERIZED_TEST(
      factory,
      assert_failure_equals_params,
      assert_failure_equals_test
    ),
    PARAMETERIZED_TEST(
      factory,
      assert_failure_not_equals_params,
      assert_failure_not_equals_test
    ),
    TEST(factory, assert_failure_to_repr_test),
    TEST(factory, assert_failure_to_str_test),
  };
}
