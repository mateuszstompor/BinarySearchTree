cmake_minimum_required(VERSION 3.7)

project(BinarySearchTree)
project(${PROJECT_NAME} C CXX)
project(${PROJECT_NAME} VERSION 0.1.0)

add_subdirectory(tests)

install(FILES ${CMAKE_SOURCE_DIR}/binary_search_tree.h DESTINATION include)
