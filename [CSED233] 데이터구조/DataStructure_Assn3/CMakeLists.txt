cmake_minimum_required(VERSION 3.27)
project(Assign3)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "-fprofile-instr-generate -fcoverage-mapping")

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
        # test/test_sort.cpp
        test/test_bst.cpp
        test/test_avl.cpp
        # test/test_open_hash_table.cpp
        # test/test_closed_hash_table.cpp
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
        Assign3Lib
        avl.cpp
        avl.h
        bst.cpp
        bst.h
        closed_hash_function.cpp
        closed_hash_function.h
        closed_hash_table.cpp
        closed_hash_table.h
        open_hash_function.cpp
        open_hash_function.h
        open_hash_table.cpp
        open_hash_table.h
        sort.cpp
        sort.h
        tree.cpp
        tree.h
        utils.cpp
        utils.h
)
target_link_libraries(
        UnitTest
        Assign3Lib
)

add_executable(
        Assign3
        pa3.cpp
)
target_link_libraries(
        Assign3
        Assign3Lib
)

