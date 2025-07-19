@echo off
REM Build script for C++ Tree Data Structures Explorer (Windows)
REM This script provides a clean build from scratch

echo === C++ Tree Data Structures Explorer Build Script (Windows) ===
echo.

REM Check if we're in the project root
if not exist "CMakeLists.txt" (
    echo Error: Please run this script from the project root directory
    exit /b 1
)

REM Check CMake version
echo Checking CMake version...
cmake --version
if errorlevel 1 (
    echo Error: CMake not found. Please install CMake and add it to your PATH.
    exit /b 1
)

REM Check C++ compiler
echo Checking C++ compiler...
where cl >nul 2>&1
if errorlevel 1 (
    echo Warning: MSVC compiler not found in PATH. Make sure you're running from a Developer Command Prompt.
    echo If using MinGW, make sure g++ is in your PATH.
) else (
    echo Found MSVC compiler
)

echo.

REM Clean previous build
echo Cleaning previous build...
if exist build rmdir /s /q build
mkdir build
cd build

REM Configure with CMake
echo Configuring with CMake...
cmake ..

REM Build the project
echo Building the project...
cmake --build . --config Release

echo.
echo === Build completed successfully! ===
echo.

REM Run tests
echo Running tests...
ctest --verbose

echo.
echo === All tests passed! ===
echo.
echo You can now run the main application with:
echo   build\Release\tree_explorer.exe
echo.
echo Or run individual tests with:
echo   build\Release\tests\binary_node_tests.exe
echo   build\Release\tests\binary_tree_set_tests.exe 