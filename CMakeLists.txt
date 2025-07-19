cmake_minimum_required(VERSION 3.10)
project(tree_explorer VERSION 1.0.0 LANGUAGES CXX)

# Generate compile_commands.json for better IDE support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
if(WIN32)
    # Windows-specific compiler flags
    # /W4 => Warning level 4
    # /Zi => Enable debug info
    # /Od => Disable optimizations
    # /O2 => Maximize speed optimizations
    # /EHsc => Enable C++ exception handling
    # /std:c++17 => Set C++ standard
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /EHsc /std:c++17")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Zi")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2")
    
    # Check if using MinGW (which supports AddressSanitizer)
    if(MINGW)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=address -g")
        set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
    endif()
else()
    # Unix-like compiler flags
    # -Wall => Enable all warnings
    # -Wextra => Enable extra warnings
    # -fsanitize=address => Enable AddressSanitizer for memory error detection
    # -g => Generate debug information
    # -O0 => Disable optimizations (debug)
    # -O3 => Maximum optimization level (release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=address -g") 
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Create the main executable
add_executable(tree_explorer main.cpp)

# Add source files
target_sources(tree_explorer PRIVATE
    src/models/binary_tree_set.cpp
)

# Set properties for the executable
set_target_properties(tree_explorer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Enable testing for CTest visibility
enable_testing()

# Add tests subdirectory
add_subdirectory(tests) 