#
# Asp string library build specification.
#

cmake_minimum_required(VERSION 3.5)

file(STRINGS version.txt VERSION)

project(asp-string
    VERSION ${VERSION}
    LANGUAGES C
    )

set(ABI_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(asp-string-class
    lib-string-class.c
    )

if(ENABLE_DEBUG)
    set_property(TARGET asp-string-class
        PROPERTY OUTPUT_NAME asp-string-class-d
        )
endif()
set_property(TARGET asp-string-class
    PROPERTY VERSION ${ABI_VERSION}
    )
if(BUILD_SHARED_LIBS)
    set_property(TARGET asp-string-class
        PROPERTY C_VISIBILITY_PRESET hidden
        )
endif()

target_compile_definitions(asp-string-class PRIVATE
    $<$<BOOL:${ENABLE_DEBUG}>:ASP_LIB_DEBUG>
    $<$<BOOL:${BUILD_SHARED_LIBS}>:USING_SHARED_LIBS>
    ASP_EXPORT_LIB_API
    )

if(BUILD_SHARED_LIBS)
    install(TARGETS asp-string-class
        DESTINATION lib
        COMPONENT Runtime
        )
endif()

if(WIN32)

    install(FILES
        string.asp
        DESTINATION ${CMAKE_INSTALL_PREFIX}/../asp/include/asp-lib
        COMPONENT Runtime
        )

else()

    install(FILES
        string.asp
        DESTINATION include/asp-lib
        COMPONENT Development
        )

endif()

if(INSTALL_DEV)

    if(NOT BUILD_SHARED_LIBS)
        install(TARGETS asp-string-class
            DESTINATION lib
            COMPONENT Development
            )
    endif()

    if(WIN32)

        install(FILES
            string-class.asps
            DESTINATION ${CMAKE_INSTALL_PREFIX}/../asp/include/asps
            COMPONENT Development
            )

    else()

        install(FILES
            string-class.asps
            DESTINATION include/asps
            COMPONENT Development
            )

    endif()

endif()
