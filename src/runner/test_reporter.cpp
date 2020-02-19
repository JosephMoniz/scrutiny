#include "scrutiny/runner/test_reporter.h"

#include <algorithm>
#include <sstream>

#include "scrutiny/runner/test_failure.h"

TestReporter::TestReporter(CliOut& cli_out) :
  _total_test_count(0),
  _completed_test_count(0),
  _passed_test_count(0),
  _failed_test_count(0),
  _failures(),
  _cli_out(cli_out) { }

TestReporter::TestCount::TestCount(size_t count) :
  _count(count) { }

void TestReporter::TestCount::operator()(TestReporter& reporter) {
  reporter._total_test_count = _count;
  reporter._cli_out.println("== Running Tests");
}

TestReporter::TestPassed::TestPassed(
  std::string_view test_name
) :
  _test_name(test_name) { }

void TestReporter::TestPassed::operator()(TestReporter& reporter) {
  constexpr auto prefix = "\x1B[36m[";
  constexpr auto outcome = "%]\x1B[0m \x1B[32mPASSED\x1B[0m ";
  reporter._completed_test_count++;
  reporter._passed_test_count++;
  auto progress = reporter._get_pct_compete();
  std::ostringstream oss;
  oss << prefix << progress << outcome << _test_name;
  reporter._cli_out.println(oss.str());
}

TestReporter::TestFailed::TestFailed(TestFailure&& failure) :
  _failure(std::move(failure)) { }

void TestReporter::TestFailed::operator()(TestReporter& reporter) {
  constexpr auto prefix = "\x1B[36m[";
  constexpr auto outcome = "%]\x1B[0m \x1B[31mFAILED\x1B[0m ";
  reporter._completed_test_count++;
  reporter._failed_test_count++;
  auto progress = reporter._get_pct_compete();
  std::ostringstream oss;
  oss << prefix << progress << outcome << _failure.test_name();
  reporter._failures.push_back(std::move(_failure));
  reporter._cli_out.println(oss.str());
}

TestReporter::TestsCompleted::TestsCompleted() = default;

void TestReporter::TestsCompleted::operator()(TestReporter& reporter) {
  std::ostringstream oss;
  if (reporter._failed_test_count > 0) {
    oss << "\n== Tests Failures\n";
    for (const auto& failure : reporter._failures) {
      oss << failure.to_string();
    }
  }
  const auto ran = std::to_string(reporter._completed_test_count);
  const auto failed = std::to_string(reporter._failed_test_count);
  const auto passed = std::to_string(reporter._passed_test_count);
  oss << "\n== Summary\n"
      << "Tests ran: " << ran << "\n"
      << "Tests failed: " << failed << "\n"
      << "Tests passed: " << passed;
  reporter._cli_out.println(oss.str());
}


size_t TestReporter::failure_count() const {
  return _failed_test_count;
}

std::string TestReporter::_get_pct_compete() const {
  float completed = _completed_test_count;
  float total = _total_test_count;
  auto pct = (int) ((completed / total) * 100);
  auto string = std::to_string(pct);
  auto signed_difference = (signed) (3 - string.size());
  auto padding = (signed_difference > 0)
    ? std::string((size_t) signed_difference, ' ')
    : "";
  return padding + string;
}

void TestReporter::handle(Message&& message) {
  const auto visitor = [&](auto&& self) {
    self(*this);
  };
  std::visit(visitor, std::move(message));
}
