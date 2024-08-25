cmake_minimum_required(VERSION 3.28)
project(bankAccount)

set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(src)

# Add main executable
add_executable(bankAccount
    src/main.cpp
    src/bankAccountImp.cpp
)

# Include the Google Test library
add_subdirectory(googletest)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Add test executable
add_executable(bankAccountTest
    tests/bankAccount_test.cpp
    src/bankAccountImp.cpp
)
target_link_libraries(bankAccountTest gtest gtest_main)

# Add test cases
add_test(NAME bankAccountTest COMMAND bankAccountTest)
