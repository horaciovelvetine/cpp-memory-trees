#!/bin/bash

# Test runner script for binary tree tests

set -e  # Exit on any error

# Move to project root if running from tests/
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$SCRIPT_DIR/.."
cd "$PROJECT_ROOT"

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure with CMake
cmake ..

# Build the project
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Run the tests
echo "Running BinaryNode tests..."
./tests/binary_node_tests

echo "Running BinaryTreeSet tests..."
# Disable AddressSanitizer container overflow detection to avoid false positives with Google Test
ASAN_OPTIONS=detect_container_overflow=0 ./tests/binary_tree_set_tests

echo "All tests completed successfully!" 