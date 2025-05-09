cmake_minimum_required(VERSION 3.22)
project(Assn2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# enable all warnings
if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# add googletest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/31993dfa6b47e11c7a6ef67cfa8af90892b9bd1c.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# setup googletest
enable_testing()
add_executable(
        UnitTest
        test_BinaryTree.cpp
        test_PriorityQueue.cpp
)
target_link_libraries(
        UnitTest
        GTest::gtest_main
        GTest::gmock_main
)
include(GoogleTest)
gtest_discover_tests(UnitTest)

# add target to test
add_library(
        Assign2Lib
        tree.cpp
        tree.h
        heap.cpp
        heap.h
)
target_link_libraries(
        UnitTest
        Assign2Lib
)

