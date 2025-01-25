#
# Asp sort library testing build specification.
#

cmake_minimum_required(VERSION 3.5)

project(test-sort VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(PROGRAM_NAME ${PROJECT_NAME})
set(SPEC_NAME api)
set(CONTEXT_HEADER context.h) 
set(CONTEXT_TYPE Context)

configure_file(
    ${test-common_SOURCE_DIR}/main-test-template.cpp
    main-test-sort.cpp)

string(CONCAT ASP_SPEC_INCLUDE
    "${PATH_NAME_SEPARATOR}${asp-sort_SOURCE_DIR}" 
    "${PATH_NAME_SEPARATOR}${test-common_SOURCE_DIR}"
    "${PATH_NAME_SEPARATOR}$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/include/asps"
    )

add_custom_command(
    OUTPUT
        "${PROJECT_BINARY_DIR}/${SPEC_NAME}.aspec"
        "${PROJECT_BINARY_DIR}/${SPEC_NAME}.c"
        "${PROJECT_BINARY_DIR}/${SPEC_NAME}.h"
    DEPENDS
        "${PROJECT_SOURCE_DIR}/${SPEC_NAME}.asps"
    COMMAND
        "${CMAKE_COMMAND}" -E env
        "ASP_SPEC_INCLUDE=${ASP_SPEC_INCLUDE}"
        aspg "-q"
        "${PROJECT_SOURCE_DIR}/${SPEC_NAME}.asps"
    )

add_executable(test-sort
    main-test-sort.cpp
    api.c
    ${test-common_SOURCE_DIR}/functions-print.cpp
    )

target_compile_definitions(test-sort PRIVATE
    ASP_TEST
    $<$<NOT:$<STREQUAL:${C_COMMAND_OPTION_PREFIXES},>>:
        COMMAND_OPTION_PREFIXES=${C_COMMAND_OPTION_PREFIXES}>
    )

target_include_directories(test-sort PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}"
    )

target_link_libraries(test-sort
    asp-sort
    aspe
    aspd
    )
