# CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CryptoExchange VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4)
endif()

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Main executable
add_executable(CryptoExchange ${SOURCES} ${HEADERS})

# Tests
enable_testing()

# FetchContent for GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Testing executable
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(run_tests ${TEST_SOURCES})

target_include_directories(run_tests PRIVATE include)
target_link_libraries(run_tests PRIVATE GTest::gtest_main)

# Source files needed for tests (exclude main.cpp)
file(GLOB_RECURSE TEST_LIB_SOURCES "src/*.cpp")
list(FILTER TEST_LIB_SOURCES EXCLUDE REGEX ".*main\\.cpp$")
target_sources(run_tests PRIVATE ${TEST_LIB_SOURCES})

include(GoogleTest)
gtest_discover_tests(run_tests)

# Print project configuration
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
