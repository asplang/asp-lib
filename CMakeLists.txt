#
# Asp libraries top-level build specification.
#

cmake_minimum_required(VERSION 3.10)

project(asplib)

option(BUILD_FOR_HOST
    "Enable/disable building tools for the host environment"
    FALSE)
option(BUILD_FOR_TARGET
    "Enable/disable building for the script engine target environment"
    FALSE)

# If no build options are chosen, build them all.
if(NOT ${BUILD_FOR_HOST} AND NOT ${BUILD_FOR_TARGET})
    set(BUILD_FOR_HOST TRUE)
    set(BUILD_FOR_TARGET TRUE)
endif()

option(BUILD_SHARED_LIBS
    "Enable/disable building of shared libraries"
    FALSE)

# Debug options.
option(ENABLE_DEBUG
    "Enable/disable debug output"
    FALSE)

add_compile_definitions(
    $<$<BOOL:${ENABLE_DEBUG}>:ASP_LIB_DEBUG>
    $<$<BOOL:${BUILD_SHARED_LIBS}>:USING_SHARED_LIBS>
    ASP_EXPORT_LIB_API
    )

include_directories(
    $<$<BOOL:${WIN32}>:${CMAKE_INSTALL_PREFIX}/../asp/include>
    .
    )

link_libraries(
    aspe
    )

link_directories(
    $<$<BOOL:${WIN32}>:${CMAKE_INSTALL_PREFIX}/../asp/lib>
    )

if(WIN32)
    if(MSVC)
        add_compile_options(/D_CRT_SECURE_NO_WARNINGS)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            # Unsupported option when using clang-cl
            add_compile_options(/Zc:preprocessor)
        endif()
    endif()
endif()

# Libraries.
add_subdirectory(codec)
add_subdirectory(crc)
