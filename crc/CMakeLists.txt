#
# Asp CRC library build specification.
#

cmake_minimum_required(VERSION 3.5)

file(STRINGS version.txt VERSION)

project(asp-crc
    VERSION ${VERSION}
    LANGUAGES C
    )

set(ABI_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(asp-crc
    lib-crc.c
    crc.c
    )

set_property(TARGET asp-crc
    PROPERTY VERSION ${ABI_VERSION})
if(BUILD_SHARED_LIBS)
    set_property(TARGET asp-crc
        PROPERTY C_VISIBILITY_PRESET hidden)
endif()

target_compile_definitions(asp-crc PRIVATE
    $<$<BOOL:${ENABLE_DEBUG}>:ASP_LIB_DEBUG>
    $<$<BOOL:${BUILD_SHARED_LIBS}>:USING_SHARED_LIBS>
    ASP_EXPORT_LIB_API
    )

if(BUILD_SHARED_LIBS)
    install(TARGETS asp-crc
        DESTINATION lib
        COMPONENT Runtime
        )
endif()

if(INSTALL_DEV)

    if(NOT BUILD_SHARED_LIBS)
        install(TARGETS asp-crc
            DESTINATION lib
            COMPONENT Development
            )
    endif()

    if(WIN32)

        install(FILES
            crc.asps
            DESTINATION ${CMAKE_INSTALL_PREFIX}/../asp/include/asps
            COMPONENT Development
            )

    else()

        install(FILES
            crc.asps
            DESTINATION include/asps
            COMPONENT Development
            )

    endif()

endif()
