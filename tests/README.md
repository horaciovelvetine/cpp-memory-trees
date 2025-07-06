# Binary Tree Tests

This directory contains comprehensive tests for the BinaryTree and BinaryTreeNode classes.

## Test Structure

- `binary_tree_node_tests.cpp` - Tests for the BinaryTreeNode class
- `binary_tree_tests.cpp` - Tests for the BinaryTree class
- `CMakeLists.txt` - CMake configuration for building tests
- `run_tests.sh` - Script to build and run all tests

## Test Coverage

### BinaryTreeNode Tests
- Constructor with different data types (int, double, string)
- Data modification
- Pointer assignment
- Null pointer handling
- Multiple nodes with different values
- Edge cases (negative values, zero, large values)
- String handling (special characters, empty strings)

### BinaryTree Tests
- Constructor and basic properties
- Insertion operations (single, multiple, duplicates, ordered, reverse ordered)
- Search operations (empty tree, existing elements, non-existing elements)
- Removal operations (empty tree, non-existing, leaf nodes, nodes with one child, nodes with two children, root node)
- Clear operations
- Traversal operations (inorder, preorder, postorder)
- Height calculations
- Edge cases and stress tests
- Different data types (int, double, string)

## Prerequisites

- CMake 3.16 or higher
- Google Test framework
- C++17 compatible compiler

## Running Tests

### Option 1: Using the test runner script
```bash
./tests/run_tests.sh
```

### Option 2: Manual build and run
```bash
# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run individual test suites
./tests/binary_tree_node_tests
./tests/binary_tree_tests

# Or run all tests with CTest
ctest --verbose
```

### Option 3: Using CTest
```bash
mkdir -p build
cd build
cmake ..
make
ctest --verbose
```

## Test Output

The tests will output detailed information about:
- Number of tests run
- Number of tests passed/failed
- Detailed failure information if any tests fail
- Test execution time

## Adding New Tests

To add new tests:

1. Add test cases to the appropriate test file
2. Follow the existing naming convention: `TestClassName_TestName`
3. Use descriptive test names that explain what is being tested
4. Include both positive and negative test cases
5. Test edge cases and error conditions

## Test Guidelines

- Each test should be independent and not rely on other tests
- Use `SetUp()` and `TearDown()` methods for common initialization/cleanup
- Test both valid and invalid inputs
- Include stress tests for performance validation
- Test all public methods of the classes
- Verify memory management (no leaks, proper cleanup)

## Memory Leak Detection (AddressSanitizer)

AddressSanitizer (ASan) is always enabled for all builds and tests. If there are any memory leaks or invalid memory accesses, ASan will print a detailed error message to the terminal when you run the tests.

- If all tests pass and you see no ASan errors, your code is leak-free!
- If ASan detects a leak or invalid access, it will print a stack trace and error details after the test output.

**Example output for a leak:**
```
==12345==ERROR: LeakSanitizer: detected memory leaks
Direct leak of 40 byte(s) in 1 object(s) allocated from:
  #0 0x7f8c2b4c3b40 in operator new(unsigned long) ...
  #1 0x7f8c2b0e2e2a in ...
```

**How to fix:**
- Check the stack trace and line numbers in the error message.
- Make sure all dynamically allocated memory is properly deleted/freed.

If you want to disable ASan, remove the `-fsanitize=address` flags from `CMakeLists.txt`. 