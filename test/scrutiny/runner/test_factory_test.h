#pragma once

#include <scrutiny.h>

std::optional<AssertFailure> test_factory_unary_test();

std::optional<AssertFailure> test_factory_parameterized_test();

Test::Group test_factory_tests(const TestFactory& factory);
