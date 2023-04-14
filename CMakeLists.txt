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


set(BST_LIBRARY_SOURCES
        BinarySearchTreeLib/BinarySearchTree.h
        benchmark/benchmark.h)

set(UNIT_TEST_SOURCES
        UnitTests/BinarySearchTreeUnitTest.cpp
        UnitTests/AVLTreeUnitTest.cpp)

add_executable(avl-app AVLTreeApp/AVLTreeApp.cpp AVLTreeLib/AVLTree.h)
add_executable(avl-benchmark AVLTreeApp/AVLBenchmark.cpp benchmark/benchmark.h AVLTreeLib/AVLTree.h)
add_executable(avl-unit-tests UnitTests/AVLTreeUnitTest.cpp AVLTreeLib/AVLTree.h)
target_link_libraries(avl-unit-tests PUBLIC gtest_main)

add_executable(bst-app BinarySearchTreeApp/BinarySearchTreeApp.cpp ${BST_LIBRARY_SOURCES})
add_executable(bst-unit-tests UnitTests/BinarySearchTreeUnitTest.cpp ${BST_LIBRARY_SOURCES})
add_executable(bst-benchmark BinarySearchTreeApp/BSTBenchmark.cpp benchmark/benchmark.h BinarySearchTreeLib/BinarySearchTree.h ${BST_LIBRARY_SOURCES})
target_link_libraries(bst-unit-tests PUBLIC gtest_main)

add_executable(all-unit-tests UnitTests/BinarySearchTreeUnitTest.cpp UnitTests/AVLTreeUnitTest.cpp BinarySearchTreeLib/BinarySearchTree.h AVLTreeLib/AVLTree.h)
target_link_libraries(all-unit-tests PUBLIC gtest_main)