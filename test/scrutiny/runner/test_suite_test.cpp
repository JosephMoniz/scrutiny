#include "scrutiny/runner/test_suite_test.h"

#include <functional>
#include <utility>

#include "_mocks/io/cli_out_mock.h"

std::optional<AssertFailure> _test_suite_pass_mock() {
  return {};
}

std::optional<AssertFailure> _test_suite_fail_mock() {
  return AssertFailure("file", "func", 3, "fail");
}

TestSuiteRunParams::TestSuiteRunParams(
  const char* _file,
  std::function<Test::Group(const TestFactory&)> _test_generator,
  int _expected_result, std::vector<std::string_view>&& _expected_output
) :
  file(_file),
  test_generator(std::move(_test_generator)),
  expected_result(_expected_result),
  expected_output(_expected_output) { }


std::vector<TestSuiteRunParams> test_suite_run_params() {
  return {
    TestSuiteRunParams(
      "main.cpp",
      [](const TestFactory& factory) -> Test::Group {
        return {
          factory.make_unary_test(
            "scrutiny/runner/test_suite_test.cpp",
            "_test_suite_pass_mock",
            _test_suite_pass_mock
          )
        };
      },
      1,
      std::vector<std::string_view> {
        "== Running Tests",
        "\x1B[36m[100%]\x1B[0m \x1B[32mPASSED\x1B[0m "
        "scrutiny/runner/test_suite_test.cpp::_test_suite_pass_mock",
        "\n== Summary\n"
        "Tests ran: 1\n"
        "Tests failed: 0\n"
        "Tests passed: 1"
      }
    ),
    TestSuiteRunParams(
      "tests/main.cpp",
      [](const TestFactory& factory) -> Test::Group {
        return {
          factory.make_unary_test(
            "tests/scrutiny/runner/test_suite_test.cpp",
            "_test_suite_pass_mock",
            _test_suite_pass_mock
          )
        };
      },
      1,
      std::vector<std::string_view> {
        "== Running Tests",
        "\x1B[36m[100%]\x1B[0m \x1B[32mPASSED\x1B[0m "
        "scrutiny/runner/test_suite_test.cpp::_test_suite_pass_mock",
        "\n== Summary\n"
        "Tests ran: 1\n"
        "Tests failed: 0\n"
        "Tests passed: 1"
      }
    ),
    TestSuiteRunParams(
      "/home/scrutiny/tests/main.cpp",
      [](const TestFactory& factory) -> Test::Group {
        return {
          factory.make_unary_test(
            "/home/scrutiny/tests/scrutiny/runner/test_suite_test.cpp",
            "_test_suite_pass_mock",
            _test_suite_pass_mock
          )
        };
      },
      1,
      std::vector<std::string_view> {
        "== Running Tests",
        "\x1B[36m[100%]\x1B[0m \x1B[32mPASSED\x1B[0m "
        "tests/scrutiny/runner/test_suite_test.cpp::_test_suite_pass_mock",
        "\n== Summary\n"
        "Tests ran: 1\n"
        "Tests failed: 0\n"
        "Tests passed: 1"
      }
    ),
    TestSuiteRunParams(
      "/home/scrutiny/tests/main.cpp",
      [](const TestFactory& factory) -> Test::Group {
        return {
          factory.make_unary_test(
            "/home/scrutiny/tests/scrutiny/runner/test_suite_test.cpp",
            "_test_suite_fail_mock",
            _test_suite_fail_mock
          )
        };
      },
      0,
      std::vector<std::string_view> {
        "== Running Tests",
        "\x1B[36m[100%]\x1B[0m \x1B[31mFAILED\x1B[0m "
        "tests/scrutiny/runner/test_suite_test.cpp::_test_suite_fail_mock",
        "\n== Tests Failures\n"
        "\n---[tests/scrutiny/runner/test_suite_test.cpp::_test_suite_fail_mock]\n"
        "source: file:3\n"
        "fail\n"
        "\n"
        "== Summary\n"
        "Tests ran: 1\n"
        "Tests failed: 1\n"
        "Tests passed: 0"
      }
    ),
    TestSuiteRunParams(
      "/home/scrutiny/tests/main.cpp",
      [](const TestFactory& factory) -> Test::Group {
        return {
          factory.make_unary_test(
            "/home/scrutiny/tests/scrutiny/runner/test_suite_test.cpp",
            "_test_suite_pass_mock",
            _test_suite_pass_mock
          ),
          factory.make_unary_test(
            "/home/scrutiny/tests/scrutiny/runner/test_suite_test.cpp",
            "_test_suite_fail_mock",
            _test_suite_fail_mock
          )
        };
      },
      0,
      std::vector<std::string_view> {
        "== Running Tests",
        "\x1B[36m[ 50%]\x1B[0m \x1B[32mPASSED\x1B[0m "
        "tests/scrutiny/runner/test_suite_test.cpp::_test_suite_pass_mock",
        "\x1B[36m[100%]\x1B[0m \x1B[31mFAILED\x1B[0m "
        "tests/scrutiny/runner/test_suite_test.cpp::_test_suite_fail_mock",
        "\n== Tests Failures\n"
        "\n---[tests/scrutiny/runner/test_suite_test.cpp::_test_suite_fail_mock]\n"
        "source: file:3\n"
        "fail\n"
        "\n"
        "== Summary\n"
        "Tests ran: 2\n"
        "Tests failed: 1\n"
        "Tests passed: 1"
      }
    )
  };
}

std::optional<AssertFailure> test_suite_run_test(
  const TestSuiteRunParams& params
) {
  // Given ...
  //
  const auto file = params.file;
  const auto& tests = params.test_generator;
  const auto& expected_result = params.expected_result;
  const auto& expected_output = params.expected_output;
  CliOutMock cli_out;
  TestReporter reporter(cli_out);
  auto test_suite = TestSuite::create(file, {tests}, reporter);

  // When ...
  //
  auto result = test_suite.run();

  // Then ...
  //
  ASSERT_EQ(result, expected_result);
  ASSERT_EQ(cli_out.println_calls(), expected_output);
  return {};
}

Test::Group test_suite_tests(const TestFactory& factory) {
  return {
    PARAMETERIZED_TEST(factory, test_suite_run_params, test_suite_run_test)
  };
}
