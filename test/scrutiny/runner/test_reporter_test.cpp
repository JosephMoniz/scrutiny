#include "scrutiny/runner/test_reporter_test.h"

#include "_mocks/io/cli_out_mock.h"

TestReporterHandleParams::TestReporterHandleParams(
  std::vector<TestReporterMessage::Type>&& _messages,
  std::vector<std::string_view>&& _expected_output
) :
  messages(std::move(_messages)),
  expected_output(std::move(_expected_output)) { }

std::vector<TestReporterHandleParams> test_reporter_handle_params() {
  return {
    {
      {
        TestReporterMessage::count(1),
        TestReporterMessage::passed(100, "test"),
        TestReporterMessage::completed(1, 0, 1, {})
      },
      {
        "== Running Tests",
        "\x1B[36m[100%]\x1B[0m \x1B[32mPASSED\x1B[0m test",
        "\n== Summary\n"
        "Tests ran: 1\n"
        "Tests failed: 0\n"
        "Tests passed: 1"
      }
    },
    {
      {
        TestReporterMessage::count(1),
        TestReporterMessage::failed(
          100, TestFailure("test", AssertFailure("file", "func", 3, "fail"))
        ),
        TestReporterMessage::completed(
          1,
          1,
          0,
          {TestFailure("test", AssertFailure("file", "func", 3, "fail"))}
        )
      },
      std::vector<std::string_view>{
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
    }
  };
}

std::optional<AssertFailure> test_reporter_handle_test(
  const TestReporterHandleParams& params
  ) {
  // Given ...
  //
  const auto& messages = params.messages;
  const auto expected_output = params.expected_output;
  CliOutMock cli_out;
  TestReporter reporter(cli_out);

  // When ...
  //
  for (const auto& message : messages) {
    reporter.handle(message);
  }

  // Then ...
  //
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
