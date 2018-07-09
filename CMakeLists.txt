cmake_minimum_required(VERSION 3.9)

project(BinarySearchTree)
project(${PROJECT_NAME} CXX)
project(${PROJECT_NAME} VERSION 0.0.0 DESCRIPTION "Binary Search Tree")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(${CMAKE_SOURCE_DIR}/benchmark/googletest)
add_subdirectory(${CMAKE_SOURCE_DIR}/benchmark)

include_directories(${CMAKE_SOURCE_DIR}/benchmark/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/benchmark/include)
include_directories(${CMAKE_SOURCE_DIR})

install(FILES ${CMAKE_SOURCE_DIR}/binary_search_tree.h DESTINATION include)

add_executable(tree_tests   ${CMAKE_SOURCE_DIR}/tests/test.cpp)
add_executable(tree_bench   ${CMAKE_SOURCE_DIR}/tests/performance.cpp)

target_link_libraries(tree_tests gtest ${GTEST_LIBRARIES})
target_link_libraries(tree_bench benchmark ${BENCHMARK_LIBRARIES})