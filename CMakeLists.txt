cmake_minimum_required(VERSION 3.7)

project(BinarySearchTree)
project(${PROJECT_NAME} CXX)
project(${PROJECT_NAME} VERSION 0.1.0)

find_package(GTest REQUIRED)
find_package (Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR})

install(FILES ${CMAKE_SOURCE_DIR}/binary_search_tree.h DESTINATION include)

add_executable(tree_tests   ${CMAKE_SOURCE_DIR}/tests/test.cpp)

target_link_libraries(tree_tests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
