#include "scrutiny/runner/test_suite.h"

#include <numeric>

size_t _test_suite_get_file_offset(std::string_view file) {
  const auto folder_offset = file.find_last_of('/');
  if (folder_offset == std::string_view::npos) {
    return 0;
  }
  const auto folder = file.substr(0, folder_offset);
  const auto parent_offset = folder.find_last_of('/');
  if (parent_offset == std::string_view::npos) {
    return folder.length() + 1;
  }
  return parent_offset + 1;
}

TestSuite::TestSuite(std::vector<Test>&& tests, TestReporter& reporter) :
  _tests(std::move(tests)),
  _test_reporter(reporter) { }

TestSuite TestSuite::create(
  const char* file,
  const std::vector<TestFactory::Generator>& test_generators,
  TestReporter& reporter
) {
  std::vector<Test> tests;
  auto file_offset = _test_suite_get_file_offset(file);
  TestFactory test_factory(file_offset);
  for (auto& test_generator : test_generators) {
    auto test_groups = test_generator(test_factory);
    for (const auto& test_group : test_groups) {
      tests.insert(tests.end(), test_group.cbegin(), test_group.cend());
    }
  }
  return TestSuite(std::move(tests), reporter);
}

int TestSuite::run() {
  _test_reporter.handle(TestReporter::TestCount(_tests.size()));
  for (const auto& test : _tests) {
      auto failure = test();
      if (failure) {
        auto message = TestReporter::TestFailed(std::move(failure.value()));
        _test_reporter.handle(std::move(message));
      } else {
        auto message = TestReporter::TestPassed(test.name());
        _test_reporter.handle(message);
      }
  }
  _test_reporter.handle(TestReporter::TestsCompleted());
  return _test_reporter.failure_count() == 0;
}
