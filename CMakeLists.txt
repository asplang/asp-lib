#
# Asp libraries top-level build specification.
#

cmake_minimum_required(VERSION 3.5)

file(STRINGS version.txt VERSION)

project(asplib
    VERSION ${VERSION})

option(INSTALL_DEV
    "Enable/disable installation of development files (e.g., headers)"
    FALSE)

option(BUILD_SHARED_LIBS
    "Enable/disable building of shared libraries"
    FALSE)
option(BUILD_TEST_TARGETS
    "Enable/disable building of tests"
    FALSE)

# Debug option.
option(ENABLE_DEBUG
    "Enable/disable debug output"
    FALSE)

if(WIN32)
    set(PATH_NAME_SEPARATOR [[;]])
    set(C_COMMAND_OPTION_PREFIXES [["-/"]])
else()
    set(PATH_NAME_SEPARATOR :)
    set(C_COMMAND_OPTION_PREFIXES [["-"]])
endif()

if(ENABLE_DEBUG)
    add_definitions(-DASP_DEBUG)
endif()

include_directories(
    $<$<BOOL:${WIN32}>:${CMAKE_INSTALL_PREFIX}/../asp/include>
    .
    )

if(ENABLE_DEBUG)
    link_libraries(
        aspe-d
        )
else()
    link_libraries(
        aspe
        )
endif()

link_directories(
    $<$<BOOL:${WIN32}>:${CMAKE_INSTALL_PREFIX}/../asp/lib>
    )

# Compile options.
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
    -pedantic -Werror
    -Wno-parenthese -Wno-switch
    -Wwrite-strings -Wpointer-arith
    )
endif()
if(WIN32 AND MSVC)
    add_compile_options(/D_CRT_SECURE_NO_WARNINGS)
endif()
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Unsupported option when using clang-cl
    add_compile_options(/Zc:preprocessor /wd4554)
endif()

# Common test files.
if(BUILD_TEST_TARGETS)
    enable_testing()
    add_subdirectory(test-common)
endif()

# Libraries.
add_subdirectory(codec)
add_subdirectory(crc)
add_subdirectory(sort)
add_subdirectory(string)

# Test cases.
if(BUILD_TEST_TARGETS)
    add_subdirectory(test)
endif()
