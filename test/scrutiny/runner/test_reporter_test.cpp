#include "scrutiny/runner/test_reporter_test.h"

#include "_mocks/io/cli_out_mock.h"

TestReporterHandleParams::TestReporterHandleParams(
  std::vector<TestReporter::Message>&& _messages,
  size_t _expected_failure_count,
  std::vector<std::string_view>&& _expected_output
) :
  messages(std::move(_messages)),
  expected_failure_count(_expected_failure_count),
  expected_output(std::move(_expected_output)) { }

std::vector<TestReporterHandleParams> test_reporter_handle_params() {
  return {
    TestReporterHandleParams(
      {
        TestReporter::TestCount(1),
        TestReporter::TestPassed("test"),
        TestReporter::TestsCompleted()
      },
      0,
      {
        "== Running Tests",
        "\x1B[36m[100%]\x1B[0m \x1B[32mPASSED\x1B[0m test",
        "\n== Summary\n"
        "Tests ran: 1\n"
        "Tests failed: 0\n"
        "Tests passed: 1"
      }
    ),
    TestReporterHandleParams(
      {
        TestReporter::TestCount(1),
        TestReporter::TestFailed(
          TestFailure("test", AssertFailure("file", "func", 3, "fail"))
        ),
        TestReporter::TestsCompleted()
      },
      1,
      std::vector<std::string_view> {
        "== Running Tests",
        "\x1B[36m[100%]\x1B[0m \x1B[31mFAILED\x1B[0m test",
        "\n== Tests Failures\n"
        "\n---[test]\n"
        "source: file:3\n"
        "fail\n"
        "\n== Summary\n"
        "Tests ran: 1\n"
        "Tests failed: 1\n"
        "Tests passed: 0"
      }
    )
  };
}

std::optional<AssertFailure> test_reporter_handle_test(
  const TestReporterHandleParams& params
  ) {
  // Given ...
  //
  const auto& messages = params.messages;
  const auto expected_failure_count = params.expected_failure_count;
  const auto expected_output = params.expected_output;
  CliOutMock cli_out;
  TestReporter reporter(cli_out);

  // When ...
  //
  for (auto message : messages) {
    reporter.handle(std::move(message));
  }

  // Then ...
  //
  ASSERT_EQ(reporter.failure_count(), expected_failure_count);
  ASSERT_EQ(cli_out.println_calls(), expected_output);
  return {};
}

Test::Group test_reporter_tests(const TestFactory& factory) {
  return {
    PARAMETERIZED_TEST(
      factory,
      test_reporter_handle_params,
      test_reporter_handle_test
    )
  };
}
