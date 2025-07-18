# Tests CMakeLists.txt

# Download and configure GoogleTest if not found
# https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

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