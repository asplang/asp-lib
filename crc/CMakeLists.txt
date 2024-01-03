#
# Asp CRC library build specification.
#

cmake_minimum_required(VERSION 3.5)

project(asp-crc
    VERSION 0.1.0.0
    LANGUAGES C
    )

set(ABI_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

if(BUILD_FOR_TARGET)

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

    install(TARGETS asp-crc)

endif()

if(BUILD_FOR_HOST)

    if(WIN32)

        install(FILES
            crc.asps
            DESTINATION ${CMAKE_INSTALL_PREFIX}/../asp/include/asps
            )

    else()

        install(FILES
            crc.asps
            DESTINATION include/asps
            )

    endif()

endif()
