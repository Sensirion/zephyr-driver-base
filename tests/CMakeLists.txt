cmake_minimum_required(VERSION 3.22)
set(CMAKE_PROJECT_NAME testing)

project(module_test)
enable_language(C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         v1.17.0
)
FetchContent_MakeAvailable(googletest)

#include module code
add_library(module OBJECT)
target_sources(module PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../src/crc_tables.c
    ${CMAKE_CURRENT_LIST_DIR}/../src/sensirion_common.c
    ${CMAKE_CURRENT_LIST_DIR}/../src/sensirion_i2c.c
)
target_include_directories(module PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/shims
)

enable_testing()

add_executable(module_test
    test_common.cpp
    test_i2c.cpp
)

target_link_libraries(module_test 
    GTest::gtest_main 
    module
)

include(GoogleTest)
gtest_discover_tests(module_test)
