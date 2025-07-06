# Tests CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

# Enable testing
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)

# Include directories for tests
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create test executables
add_executable(binary_node_tests binary_node_tests.cpp)
add_executable(binary_tree_set_tests binary_tree_set_tests.cpp)

# Link with GTest and your source files
target_link_libraries(binary_node_tests GTest::gtest GTest::gtest_main)
target_link_libraries(binary_tree_set_tests GTest::gtest GTest::gtest_main)

# Add source files for the binary tree tests
target_sources(binary_tree_set_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src/models/binary_tree_set.cpp
)

# Set properties for test executables
set_target_properties(binary_node_tests binary_tree_set_tests PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Add tests to CTest
add_test(NAME BinaryTreeNodeTests COMMAND binary_node_tests)
add_test(NAME BinaryTreeTests COMMAND binary_tree_set_tests) 