#pragma once

#include <cstdlib>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

#include "scrutiny/io/cli_out.h"
#include "scrutiny/runner/test_failure.h"
#include "test_reporter_message.h"

class TestReporter final {

  CliOut& _cli_out;

  static std::string _pad_progress(int progress);

  void _visit_message(const TestReporterMessage::Count& message);

  void _visit_message(const TestReporterMessage::Passed& message);

  void _visit_message(const TestReporterMessage::Failed& message);

  void _visit_message(const TestReporterMessage::Completed& message);

public:

  explicit TestReporter(CliOut& cli_out);

  void handle(const TestReporterMessage::Type& message);

};
