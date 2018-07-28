cmake_minimum_required(VERSION 3.5)
project(allocator)

set(CMAKE_CXX_STANDARD 14)

add_executable(allocator main.cpp allocator.h simple_list.h)

set_target_properties(allocator PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "$ENV{TRAVIS_BUILD_NUMBER}")

set(CPACK_PACKAGE_CONTACT osmironov@gmail.com)

include(CPack)