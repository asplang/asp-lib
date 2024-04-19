#
# Asp codec library build specification.
#

cmake_minimum_required(VERSION 3.5)

project(asp-codec
    VERSION 0.2.1.0
    LANGUAGES C
    )

set(ABI_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

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

target_compile_definitions(asp-codec PRIVATE
    $<$<BOOL:${ENABLE_DEBUG}>:ASP_LIB_DEBUG>
    $<$<BOOL:${BUILD_SHARED_LIBS}>:USING_SHARED_LIBS>
    ASP_EXPORT_LIB_API
    )

if(BUILD_SHARED_LIBS)
    install(TARGETS asp-codec
        DESTINATION lib
        COMPONENT Runtime
        )
endif()

if(INSTALL_DEV)

    if(NOT BUILD_SHARED_LIBS)
        install(TARGETS asp-codec
            DESTINATION lib
            COMPONENT Development
            )
    endif()

    if(WIN32)

        install(FILES
            codec.asps
            DESTINATION ${CMAKE_INSTALL_PREFIX}/../asp/include/asps
            COMPONENT Development
            )

    else()

        install(FILES
            codec.asps
            DESTINATION include/asps
            COMPONENT Development
            )

    endif()

endif()
