# C++ Tree Data Structures Explorer

A C++ project for exploring tree data structures using CMake and GoogleTests for testing. 

## Project Structure

```
cpp-memory-trees/
├── CMakeLists.txt               # Main CMake configuration
├── main.cpp                     # Main application entry point
├── include/
│   └── models/                  # Header files
│       ├── binary_node.hpp      # Binary node template class
│       └── binary_tree_set.hpp  # Binary tree set implementation
├── src/
│   └── models/                  # Source implementations
│       └── binary_tree_set.cpp  # Binary tree set methods
└── tests/
    ├── CMakeLists.txt           # Test configuration
    ├── run_tests.sh             # Test runner script
    ├── binary_node_tests.cpp    # Binary node unit tests
    └── binary_tree_set_tests.cpp # Binary tree set unit tests
```

## Prerequisites

- **CMake 3.5 or higher**
- **C++17 compatible compiler**:
  - GCC 7+ or Clang 5+ (Linux/macOS)
  - MSVC 2017+ (Windows)
- **Make** (or equivalent build system)

## Building the Project

### Quick Start (Recommended)

```bash
# Use the automated build script
./build.sh
```

This script will:
- Check prerequisites (CMake, C++ compiler)
- Clean any previous build
- Configure and build the project
- Run all tests automatically

### Manual Build

```bash
# Create and enter build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run the main application
./tree_explorer
```

### Build Options

```bash
# Debug build (default)
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build with optimizations
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build with specific number of jobs (faster compilation)
make -j$(nproc)  # Linux
make -j$(sysctl -n hw.ncpu)  # macOS
make -j4  # Windows or fallback
```

### Build Features

- **Address Sanitizer**: Enabled by default for memory error detection
- **Compile Commands**: Generates `compile_commands.json` for IDE support
- **Warning Flags**: Enables `-Wall -Wextra` for comprehensive warnings

## Running Tests

### Using CTest (Recommended)

```bash
# From the build directory!!
make
ctest --verbose

# Run specific tests
ctest -R BinaryNodeTests
ctest -R BinaryTreeTests
```

### Using the Test Runner Script

```bash
# From project root
./tests/run_tests.sh

# Or from tests directory
cd tests
./run_tests.sh
```

### Running Individual Test Executables

```bash
# From build directory
./tests/binary_node_tests
./tests/binary_tree_set_tests

# With verbose output
./tests/binary_node_tests --gtest_verbose
./tests/binary_tree_set_tests --gtest_verbose
```

### Test Coverage

**BinaryNode Tests:**
- Construction with different data types (int, double, string)
- Read-only access methods
- Special string cases (Unicode, special characters)
- Const correctness

**BinaryTreeSet Tests:**
- Basic operations (insert, contains, find, erase)
- Tree traversal (inorder, preorder, postorder)
- Tree properties (size, height, empty)
- Complex operations (merge, clear)
- Edge cases and error handling

## Development

### Adding New Tests

1. Create a new test file in `tests/`
2. Add the test executable to `tests/CMakeLists.txt`
3. Link with Google Test libraries
4. Add to CTest configuration

Example:
```cmake
add_executable(my_new_tests my_new_tests.cpp)
target_link_libraries(my_new_tests GTest::gtest GTest::gtest_main)
add_test(NAME MyNewTests COMMAND my_new_tests)
```

## Troubleshooting

**Build fails with CMake version error:**
- Ensure CMake 3.5+ is installed
- Update CMake: `brew install cmake` (macOS) or `sudo apt install cmake` (Ubuntu)

**Address Sanitizer errors:**
- These are intentional for testing memory safety
- Disable with: `ASAN_OPTIONS=detect_container_overflow=0`

**Google Test not found:**
- The project automatically downloads Google Test via FetchContent
- Ensure internet connection during first build

**Permission denied on test script:**
```bash
chmod +x tests/run_tests.sh
```

### Platform-Specific Notes

**macOS:**
- Install dependencies: `brew install cmake make`
- Use `sysctl -n hw.ncpu` for parallel builds

**Linux:**
- Install dependencies: `sudo apt install cmake make g++`
- Use `nproc` for parallel builds

**Windows:**
- Install Visual Studio with C++ tools
- Use `cmake --build .` instead of `make`

## License

This project is open source and available under the MIT License. 
