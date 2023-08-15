#
# Asp codec library build specification.
#

cmake_minimum_required(VERSION 3.10)

project(asp-codec
    VERSION 0.1.0.0
    LANGUAGES C
    )

set(ABI_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

if(BUILD_FOR_TARGET)

    set(CMAKE_C_STANDARD 99)
    set(CMAKE_C_STANDARD_REQUIRED True)

    add_library(asp-codec
            lib-codec.c
            )

    set_property(TARGET asp-codec
        PROPERTY VERSION ${ABI_VERSION})
    if(BUILD_SHARED_LIBS)
        set_property(TARGET asp-codec
            PROPERTY C_VISIBILITY_PRESET hidden)
    endif()

    install(TARGETS asp-codec)

endif()

if(BUILD_FOR_HOST)

    if(WIN32)

        install(FILES
            codec.asps
            DESTINATION ${CMAKE_INSTALL_PREFIX}/../asp/include/asps
            )

    else()

        install(FILES
            codec.asps
            DESTINATION include/asps
            )

    endif()

endif()
