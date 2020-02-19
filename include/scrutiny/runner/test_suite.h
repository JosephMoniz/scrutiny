#pragma once

#include <vector>

#include "scrutiny/io/cli_out_impl.h"
#include "scrutiny/runner/test.h"
#include "scrutiny/runner/test_factory.h"
#include "scrutiny/runner/test_reporter.h"

#define RUN_TESTS(GROUPS) do { \
  CliOutImpl __cli_out; \
  TestReporter __test_reporter(__cli_out); \
  return TestSuite::create(__FILE__, GROUPS, __test_reporter).run(); \
} while(0)

class TestSuite final {

  std::vector<Test> _tests;

  TestReporter& _test_reporter;

public:

  explicit TestSuite(std::vector<Test>&& tests, TestReporter& reporter);

  static TestSuite create(
    const char* file,
    const std::vector<TestFactory::Generator>& test_generators,
    TestReporter& reporter
  );

  [[nodiscard]]
  int run();

};
