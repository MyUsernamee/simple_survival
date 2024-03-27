
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

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(simple_survival ${SOURCES})

# Add the tests and all files except main.cpp
list(FILTER SOURCES EXCLUDE REGEX "main.cpp")
add_executable(tests tests/test.cpp ${SOURCES})

add_test(NAME tests COMMAND tests)

target_link_libraries(simple_survival raylib)
target_link_libraries(tests raylib)
