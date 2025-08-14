#
# Asp library test cases.
#

cmake_minimum_required(VERSION 3.5)

set(tests
    crc-piecemeal
    crc-simple
    sort-sort-0
    sort-sort-1
    sort-sort-2a
    sort-sort-2b
    sort-sort-4
    sort-sorted-0
    sort-sorted-1
    sort-sorted-2a
    sort-sorted-2b
    sort-sorted-range
    sort-sorted-string
    sort-stable
    string-case
    string-class1
    string-class2
    string-count
    string-ends
    string-find
    string-join
    string-just
    string-partition
    string-replace
    string-split
    string-splitlines
    string-strip
    string-tabs
    string-translate
    string-zfill
    )

set(REGRESSION_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/regression-data"
    CACHE PATH "Regression data directory")

add_custom_target(clean-regression-data
    COMMAND ${CMAKE_COMMAND} -E rm -Rf "${REGRESSION_DATA_DIR}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${REGRESSION_DATA_DIR}"
    )

set(generate_regression_data)

foreach(test_name ${tests})

    set(source ${test_name}.asp)

    add_test(NAME ${test_name}
        COMMAND ${CMAKE_COMMAND}
            -D "INCLUDE_PATH=:${asp-string_SOURCE_DIR}"
            -D "TEST_NAME=${test_name}"
            -D "SOURCE_FILE=${CMAKE_CURRENT_SOURCE_DIR}/${source}"
            -D "BINARY_NAME=${test_name}"
            -D "ASPEC_FILE=${test-lib_BINARY_DIR}/api.aspec"
            -D "DRIVER=$<TARGET_FILE:test-lib>"
            -D "OUTPUT_DIR=${CMAKE_CURRENT_BINARY_DIR}/regression-data"
            -D "COMPARE_DIR=${REGRESSION_DATA_DIR}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/run-test.cmake"
        VERBATIM
        )

    # Custom target to generate regression data for this test case.
    add_custom_target(generate-regression-data-${test_name}
        COMMAND ${CMAKE_COMMAND}
            -D "INCLUDE_PATH=:${asp-string_SOURCE_DIR}"
            -D "TEST_NAME=${test_name}"
            -D "SOURCE_FILE=${CMAKE_CURRENT_SOURCE_DIR}/${source}"
            -D "BINARY_NAME=${test_name}"
            -D "ASPEC_FILE=${test-lib_BINARY_DIR}/api.aspec"
            -D "DRIVER=$<TARGET_FILE:test-lib>"
            -D "OUTPUT_DIR=${REGRESSION_DATA_DIR}"
            -P "${CMAKE_CURRENT_SOURCE_DIR}/run-test.cmake"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${test_nam}"
        VERBATIM
        )
    add_dependencies(generate-regression-data-${test_name}
        clean-regression-data
        )
    list(APPEND generate_regression_data
        generate-regression-data-${test_name}
        )

endforeach()

# Custom target to generate regression data for all test cases.
add_custom_target(generate-regression-data)
add_dependencies(generate-regression-data ${generate_regression_data})
