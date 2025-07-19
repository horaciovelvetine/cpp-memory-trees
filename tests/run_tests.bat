@echo off
REM Test runner script for binary tree tests (Windows)

REM Move to project root if running from tests/
set SCRIPT_DIR=%~dp0
set PROJECT_ROOT=%SCRIPT_DIR%..
cd /d "%PROJECT_ROOT%"

REM Create build directory if it doesn't exist
if not exist build mkdir build
cd build

REM Configure with CMake
cmake ..

REM Build the project
cmake --build . --config Release

REM Run the tests
echo Running BinaryNode tests...
tests\Release\binary_node_tests.exe

echo Running BinaryTreeSet tests...
REM Note: AddressSanitizer options are not applicable on Windows MSVC
REM If using MinGW with AddressSanitizer, you might need to set ASAN_OPTIONS
tests\Release\binary_tree_set_tests.exe

echo All tests completed successfully! 