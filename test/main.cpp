#include "scrutiny.h"

#include "scrutiny/runner/test_factory_test.h"
#include "scrutiny/assert/assert_failure_test.h"
#include "scrutiny/assert/bool_test.h"
#include "scrutiny/assert/eq_test.h"
#include "scrutiny/assert/numeric_test.h"
#include "scrutiny/assert/optional_test.h"
#include "scrutiny/assert/str_test.h"
#include "scrutiny/assert/vector_test.h"
#include "scrutiny/runner/test_failure_test.h"
#include "scrutiny/runner/test_reporter_test.h"
#include "scrutiny/runner/test_suite_test.h"
#include "scrutiny/runner/test_test.h"

int main() {
  std::vector<TestFactory::Generator> test_groups = {
    test_factory_tests,
    assert_failure_tests,
    bool_assert_eq_tests,
    assert_eq_tests,
    numeric_assert_eq_tests,
    optional_assert_eq_tests,
    str_assert_eq_tests,
    vector_assert_eq_tests,
    test_failure_tests,
    test_reporter_tests,
    test_suite_tests,
    test_tests
  };
  RUN_TESTS(test_groups);
}
