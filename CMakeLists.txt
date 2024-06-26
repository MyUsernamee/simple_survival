
# Cmake Version
cmake_minimum_required(VERSION 3.20)

project(simple_survival)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# raylib-cpp
add_subdirectory(dependencies/raylib-cpp)
# json
add_subdirectory(dependencies/json)

# Copy assets folder on build
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# If we are on windows move the executable to the build folder
if(WIN32)

endif()

# Include Directories
include_directories(include)
include_directories(dependencies/raylib-cpp/include)
include_directories(dependencies/json/include)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(simple_survival ${SOURCES})

# Add the tests and all files except main.cpp
list(FILTER SOURCES EXCLUDE REGEX "main.cpp")
add_executable(tests tests/test.cpp ${SOURCES})

add_test(NAME tests COMMAND tests)

target_link_libraries(simple_survival raylib)
target_link_libraries(tests raylib)
