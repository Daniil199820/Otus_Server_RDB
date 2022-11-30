cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(join_server VERSION ${PROJECT_VERSION})

find_package(Threads)

add_executable(join_server main.cpp )

set_target_properties(join_server PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_link_libraries(join_server
        ${CMAKE_THREAD_LIBS_INIT}
        dl
        ${Boost_LIBRARIES}
        )

target_include_directories(
        join_server PRIVATE
        ${Boost_INCLUDE_DIR}
        )


if (MSVC)

        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    
        target_compile_options(join_server PRIVATE
            /W3
        )
    
        target_compile_options(join_server PRIVATE
            /W3
        )
    else ()
        target_compile_options(join_server PRIVATE
            -Wall -Wextra -pedantic 
        )
    
        target_compile_options(join_server PRIVATE
            -Wall -Wextra -pedantic 
        )
endif()

install(TARGETS join_server RUNTIME DESTINATION bin)


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)