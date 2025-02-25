#
# Asp sort library build specification.
#

cmake_minimum_required(VERSION 3.5)

file(STRINGS version.txt VERSION)

project(asp-sort
    VERSION ${VERSION}
    LANGUAGES C
    )

set(ABI_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(asp-sort
    lib-sort.c
    lib-sorted.c
    )

if(ENABLE_DEBUG)
    set_property(TARGET asp-sort
        PROPERTY OUTPUT_NAME asp-sort-d
        )
endif()
set_property(TARGET asp-sort
    PROPERTY VERSION ${ABI_VERSION}
    )
if(BUILD_SHARED_LIBS)
    set_property(TARGET asp-sort
        PROPERTY C_VISIBILITY_PRESET hidden
        )
endif()

target_compile_definitions(asp-sort PRIVATE
    $<$<BOOL:${ENABLE_DEBUG}>:ASP_LIB_DEBUG>
    $<$<BOOL:${BUILD_SHARED_LIBS}>:USING_SHARED_LIBS>
    ASP_EXPORT_LIB_API
    )

if(BUILD_SHARED_LIBS)
    install(TARGETS asp-sort
        DESTINATION lib
        COMPONENT Runtime
        )
endif()

if(INSTALL_DEV)

    if(NOT BUILD_SHARED_LIBS)
        install(TARGETS asp-sort
            DESTINATION lib
            COMPONENT Development
            )
    endif()

    if(WIN32)

        install(FILES
            sort.asps
            DESTINATION ${CMAKE_INSTALL_PREFIX}/../asp/include/asps
            COMPONENT Development
            )

    else()

        install(FILES
            sort.asps
            DESTINATION include/asps
            COMPONENT Development
            )

    endif()

endif()

if(BUILD_TEST_TARGETS)
    add_subdirectory(test)
endif()
