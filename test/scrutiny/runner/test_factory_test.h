#pragma once

#include <scrutiny.h>

std::optional<AssertFailure> test_factory_make_unary_test_test();

std::optional<AssertFailure> test_factory_make_parameterized_test_test();

Test::Group test_factory_tests(const TestFactory& factory);