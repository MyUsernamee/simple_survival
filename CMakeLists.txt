
# Cmake Version
cmake_minimum_required(VERSION 3.23)

project(simple_survival)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

find_package(raylib 5.0 REQUIRED)

# raylib-cpp
add_subdirectory(dependencies/raylib-cpp)

# Include Directories
include_directories(include)
include_directories(dependencies/raylib-cpp/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(simple_survival ${SOURCES})

target_link_libraries(simple_survival raylib)