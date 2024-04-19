#
# Asp libraries top-level build specification.
#

cmake_minimum_required(VERSION 3.5)

project(asplib
    VERSION 0.2.1.0)

option(INSTALL_DEV
    "Enable/disable installation of development files (e.g., headers)"
    FALSE)

option(BUILD_SHARED_LIBS
    "Enable/disable building of shared libraries"
    FALSE)

# Debug options.
option(ENABLE_DEBUG
    "Enable/disable debug output"
    FALSE)

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
