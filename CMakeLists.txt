cmake_minimum_required(VERSION 3.16)
project(binary-trees)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)
FetchContent_MakeAvailable(googletest)


set(LIBRARY_SOURCES
        AVLTreeLib/AVLTree.h
        AVLTreeLib/AVLTreeLib.cpp
        BinarySearchTreeLib/BinarySearchTree.h
        BinarySearchTreeLib/BinarySearchTreeLib.cpp
        benchmark/benchmark.h)

set(UNIT_TEST_SOURCES
        UnitTests/BinarySearchTreeUnitTest.cpp
        UnitTests/AVLTreeUnitTest.cpp)

add_executable(avl-app AVLTreeApp/AVLTreeApp.cpp ${LIBRARY_SOURCES})
add_executable(bst-app BinarySearchTreeApp/BinarySearchTreeApp.cpp ${LIBRARY_SOURCES})

add_executable(unitTests ${UNIT_TEST_SOURCES} ${LIBRARY_SOURCES})
target_link_libraries(unitTests PUBLIC gtest_main)