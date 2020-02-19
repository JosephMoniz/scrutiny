cmake_minimum_required(VERSION 3.12)
project(scrutiny)

set(CMAKE_CXX_STANDARD 17)

set(INCLUDE_FILES
        include/scrutiny.h
        include/scrutiny/assert/assert_failure.h
        include/scrutiny/assert/eq.h
        include/scrutiny/runner/public.h
        include/scrutiny/runner/test.h
        include/scrutiny/runner/test_reporter.h
        include/scrutiny/runner/test_suite.h
        include/scrutiny/runner/test_failure.h
        include/scrutiny/runner/public.h
        include/scrutiny/assert/public.h
        include/scrutiny/io/cli_out.h
        include/scrutiny/io/cli_out_impl.h
        include/scrutiny/runner/test_factory.h
        include/scrutiny/assert/bool.h
        include/scrutiny/assert/str.h
        include/scrutiny/assert/numeric.h
        include/scrutiny/assert/vector.h
        include/scrutiny/assert/optional.h)

set(SOURCE_FILES
        src/runner/test.cpp
        src/runner/test_reporter.cpp
        src/runner/test_suite.cpp
        src/assert/assert_failure_assert.cpp
        src/runner/test_failure.cpp
        src/io/cli_out_impl.cpp
        src/runner/test_factory.cpp
        src/assert/bool.cpp
        src/assert/numeric.cpp
        src/assert/str.cpp)

set(TEST_FILES
        test/scrutiny/assert/assert_failure_test.cpp
        test/scrutiny/assert/assert_failure_test.h
        test/_assert/assert_failure_assert.h
        test/scrutiny/runner/test_failure_test.cpp
        test/scrutiny/runner/test_failure_test.h
        test/scrutiny/runner/test_reporter_test.cpp
        test/scrutiny/runner/test_reporter_test.h
        test/_mocks/io/cli_out_mock.cpp
        test/_mocks/io/cli_out_mock.h
        test/scrutiny/runner/test_suite_test.cpp
        test/scrutiny/runner/test_suite_test.h
        test/scrutiny/runner/test_test.cpp
        test/scrutiny/runner/test_test.h
        test/_assert/test_failure_assert.h
        test/scrutiny/runner/test_factory_test.cpp
        test/scrutiny/runner/test_factory_test.h
        test/scrutiny/assert/bool_test.cpp
        test/scrutiny/assert/bool_test.h
        test/scrutiny/assert/eq_test.cpp
        test/scrutiny/assert/eq_test.h
        test/scrutiny/assert/numeric_test.cpp
        test/scrutiny/assert/numeric_test.h
        test/scrutiny/assert/optional_test.cpp
        test/scrutiny/assert/optional_test.h
        test/scrutiny/assert/str_test.cpp
        test/scrutiny/assert/str_test.h
        test/scrutiny/assert/vector_test.cpp
        test/scrutiny/assert/vector_test.h)

set(STATIC_DEPENDENCIES)

set(INCLUDE_DEPENDENCIES
        ${FORMAT_INCLUDE_DIRECTORY})

add_library(scrutiny STATIC
        ${INCLUDE_FILES}
        ${SOURCE_FILES})

add_executable(scrutiny_tests
        ${INCLUDE_FILES}
        ${TEST_FILES}
        test/main.cpp)

target_include_directories(scrutiny PUBLIC
        include
        ${FORMAT_INCLUDE_DIRECTORY})

target_include_directories(scrutiny_tests PUBLIC
        include
        test)

target_link_libraries(scrutiny
        ${STATIC_DEPENDENCIES})

target_link_libraries(scrutiny_tests
        scrutiny
        ${STATIC_DEPENDENCIES})