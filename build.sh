#!/bin/bash

# Build script for C++ Tree Data Structures Explorer
# This script provides a clean build from scratch

set -e  # Exit on any error

echo "=== C++ Tree Data Structures Explorer Build Script ==="
echo ""

# Check if we're in the project root
if [ ! -f "CMakeLists.txt" ]; then
    echo "Error: Please run this script from the project root directory"
    exit 1
fi

# Check CMake version
echo "Checking CMake version..."
cmake_version=$(cmake --version | head -n1 | cut -d' ' -f3)
echo "Found CMake version: $cmake_version"

# Check C++ compiler
echo "Checking C++ compiler..."
if command -v g++ &> /dev/null; then
    echo "Found GCC: $(g++ --version | head -n1)"
elif command -v clang++ &> /dev/null; then
    echo "Found Clang: $(clang++ --version | head -n1)"
else
    echo "Error: No C++ compiler found. Please install GCC or Clang."
    exit 1
fi

echo ""

# Clean previous build
echo "Cleaning previous build..."
rm -rf build
mkdir -p build
cd build

# Configure with CMake
echo "Configuring with CMake..."
cmake ..

# Build the project
echo "Building the project..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "=== Build completed successfully! ==="
echo ""

# Run tests
echo "Running tests..."
ctest --verbose

echo ""
echo "=== All tests passed! ==="
echo ""
echo "You can now run the main application with:"
echo "  ./build/tree_explorer"
echo ""
echo "Or run individual tests with:"
echo "  ./build/tests/binary_node_tests"
echo "  ./build/tests/binary_tree_set_tests" 