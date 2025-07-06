# C++ Tree Data Structures Explorer

A basic C++ project for exploring tree data structures using CMake.

## Project Structure

```
cpp-memory-trees/
├── CMakeLists.txt               # Main CMake configuration
├── main.cpp                     # Main application
├── include/
│   └── models/                  # Main model header files
│       └── binary_tree_set.hpp 
└── src/
    └── models/                  # Main model implementations
        └── binary_node.cpp      # Simplest Binary Node 
        └── binary_tree_set.cpp  # Simplest Binary Tree 
```

## Building the Project

### Prerequisites

- CMake 3.16 or higher
- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)

### Build Instructions

```bash
# Create build directory
mkdir build && cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run the application
./tree_explorer
```

### Build Options

```bash
# Debug build
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build with optimizations
cmake -DCMAKE_BUILD_TYPE=Release ..
```

## License

This project is open source and available under the MIT License. 
