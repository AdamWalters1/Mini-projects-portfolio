cmake_minimum_required(VERSION 3.28)
project(search_sort_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(search_sort_1
        src/list_operations.cpp
        src/main.cpp
)

add_subdirectory(googletest)

enable_testing()
# This line should include the directories where the Google Test headers are located
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add test executable
add_executable(search_sort_1_test
    tests/list_operations_tests.cpp
)
target_link_libraries(search_sort_1_test gtest gtest_main)

# Add test cases
add_test(NAME search_sort_1_test COMMAND search_sort_1_test)

