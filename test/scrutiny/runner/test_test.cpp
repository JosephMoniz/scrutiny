#include "scrutiny/runner/test_test.h"

#include "_assert/test_failure_assert.h"

std::optional<AssertFailure> _test_pass_mock() {
  return {};
}

std::optional<AssertFailure> _test_fail_mock() {
  return AssertFailure("file", "func", 3, "fail");
}

std::optional<AssertFailure> test_name_test() {
  // Given ...
  //
  Test test("pass", _test_pass_mock);

  // When ...
  //
  const auto result = test.name();

  // Then ...
  //
  ASSERT_EQ(result, "pass");
  return {};
}

TestRunParams::TestRunParams(
  Test&& _test,
  std::optional<TestFailure>&& _expected_result
) :
 test(std::move(_test)),
 expected_result(std::move(_expected_result)) { }

std::vector<TestRunParams> test_run_params() {
  return {
    TestRunParams(
      Test("pass", _test_pass_mock),
      {}
    ),
    TestRunParams(
      Test("fail", _test_fail_mock),
      TestFailure("fail", AssertFailure("file", "func", 3, "fail"))
    ),
  };
}

std::optional<AssertFailure> test_run_test(const TestRunParams& params) {
  // Given ...
  //
  const auto& test = params.test;
  const auto& expected_result = params.expected_result;

  // When ...
  //
  const auto result = test();

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  return {};
}

Test::Group test_tests(const TestFactory& factory) {
  return {
    TEST(factory, test_name_test),
    PARAMETERIZED_TEST(factory, test_run_params, test_run_test)
  };
}

