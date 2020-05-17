#include "scrutiny/runner/test_suite.h"

#include <functional>

#include "scrutiny/runner/test_name_factory.h"

TestSuite::TestSuite(std::vector<Test>&& tests, TestReporter& reporter) :
  _tests(std::move(tests)),
  _test_state(),
  _test_reporter(reporter) { }

TestSuite TestSuite::create(
  const char* file,
  const std::vector<TestFactory::Generator>& test_generators,
  TestReporter& reporter
) {
  std::vector<Test> tests;
  const auto test_name_factory = TestNameFactory::create(file);
  TestFactory test_factory(test_name_factory);
  for (auto& test_generator : test_generators) {
    auto test_groups = test_generator(test_factory);
    for (const auto& test_group : test_groups) {
      tests.insert(tests.end(), test_group.cbegin(), test_group.cend());
    }
  }
  return TestSuite(std::move(tests), reporter);
}

void TestSuite::_start() {
  auto count_state_msg = TestStateMessage::count(_tests.size());
  auto count_reporter_msg = _test_state.handle(count_state_msg);
  _test_reporter.handle(count_reporter_msg);
}

void TestSuite::_step(const Test& test) {
  auto failure = test();
  auto state_msg = failure
    ? TestStateMessage::failed(failure.value())
    : TestStateMessage::passed(test.name());
  auto reporter_msg = _test_state.handle(state_msg);
  _test_reporter.handle(reporter_msg);
}

int TestSuite::_finish() {
  auto final_state_msg = TestStateMessage::completed();
  auto final_reporter_msg = _test_state.handle(final_state_msg);
  _test_reporter.handle(final_reporter_msg);
  return _test_state.failure_count() == 0;
}

int TestSuite::run() {
  _start();
  const auto step = std::bind(&TestSuite::_step, this, std::placeholders::_1);
  std::for_each(_tests.cbegin(), _tests.cend(), step);
  return _finish();
}
