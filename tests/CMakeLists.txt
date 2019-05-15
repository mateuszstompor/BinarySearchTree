cmake_minimum_required(VERSION 3.7)

project(BinarySearchTreeTests)
project(${PROJECT_NAME} CXX C)
project(${PROJECT_NAME} VERSION 0.1.0)

find_package(GTest REQUIRED)
find_package (Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(tree_tests ${CMAKE_SOURCE_DIR}/test.cpp)

target_link_libraries(tree_tests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
