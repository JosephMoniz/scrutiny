#pragma once

#include "scrutiny.h"

std::optional<AssertFailure> assert_eq_not_implemented_test();

Test::Group assert_eq_tests(const TestFactory& factory);
