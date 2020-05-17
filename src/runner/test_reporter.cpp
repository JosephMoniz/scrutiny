#include "scrutiny/runner/test_reporter.h"

#include <algorithm>
#include <sstream>

TestReporter::TestReporter(CliOut& cli_out) :
  _cli_out(cli_out) { }

std::string TestReporter::_pad_progress(int progress) {
  std::string result;
  const auto progress_str = std::to_string(progress);
  const auto padding_size = 3 - progress_str.length();
  result.reserve(3);
  result.insert(0, padding_size, ' ');
  result.append(progress_str);
  return result;
}

void TestReporter::_visit_message(const TestReporterMessage::Count& message) {
  _cli_out.println("== Running Tests");
}

void TestReporter::_visit_message(const TestReporterMessage::Passed& message) {
  std::ostringstream oss;
  oss << "\x1B[36m["
      << _pad_progress(message.progress)
      << "%]\x1B[0m \x1B[32mPASSED\x1B[0m "
      << message.test_name;
  _cli_out.println(oss.str());
}

void TestReporter::_visit_message(const TestReporterMessage::Failed& message) {
  std::ostringstream oss;
  oss << "\x1B[36m["
      << _pad_progress(message.progress)
      << "%]\x1B[0m \x1B[31mFAILED\x1B[0m "
      << message.failure.test_name();
  _cli_out.println(oss.str());
}

void TestReporter::_visit_message(
  const TestReporterMessage::Completed& message
) {
  std::ostringstream oss;
  if (!message.failures.empty()) {
    oss << "\n== Tests Failures\n";
    for (const auto& failure : message.failures) {
      oss << failure.to_string();
    }
  }
  const auto ran = std::to_string(message.completed_test_count);
  const auto failed = std::to_string(message.failed_test_count);
  const auto passed = std::to_string(message.passed_test_count);
  oss << "\n== Summary\n"
      << "Tests ran: " << ran << "\n"
      << "Tests failed: " << failed << "\n"
      << "Tests passed: " << passed;
  _cli_out.println(oss.str());
}

void TestReporter::handle(const TestReporterMessage::Type& message) {
  const auto visitor = [this](const auto& self) -> void {
    _visit_message(self);
  };
  std::visit(visitor, message);
}
