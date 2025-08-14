set(ENV{ASP_INCLUDE} "${INCLUDE_PATH}")

set(test_result 0)

if(${test_result} EQUAL 0)
    execute_process(
        COMMAND aspc "${ASPEC_FILE}" "${SOURCE_FILE}"
        RESULT_VARIABLE test_result
        )
endif()

if(${test_result} EQUAL 0)
    file(MAKE_DIRECTORY "${OUTPUT_DIR}")
    execute_process(
        COMMAND "${DRIVER}" "${BINARY_NAME}"
        OUTPUT_FILE "${OUTPUT_DIR}/${TEST_NAME}.out.txt"
        RESULT_VARIABLE test_result
        )
endif()

if(NOT "${COMPARE_DIR}" STREQUAL "" AND ${test_result} EQUAL 0)
    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E compare_files
            "${OUTPUT_DIR}/${TEST_NAME}.out.txt"
            "${COMPARE_DIR}/${TEST_NAME}.out.txt"
        RESULT_VARIABLE test_result
        )
endif()

if (NOT ${test_result} EQUAL 0)
    message(FATAL_ERROR "${TEST_NAME}: Test failed")
endif()
