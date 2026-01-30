cmake_minimum_required(VERSION 3.14)

# Project name and settings
project(MySharedLibrary LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../..")

# Path to godot-cpp
set(GODOT_CPP_PATH "godot-cpp")
set(STATIC_LIB_PATH "${GODOT_CPP_PATH}/bin")
set(STATIC_LIB_NAME "godot-cpp")

# Include directories for godot-cpp headers and source headers
include_directories(
    "${GODOT_CPP_PATH}/gdextension"
    "${GODOT_CPP_PATH}/include"
    "${GODOT_CPP_PATH}/gen/include"
    "src"
)

# Collect all .cpp files in the src directory
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

# Add the shared library target
add_library(MySharedLibrary SHARED ${SOURCE_FILES})

# Link against the godot-cpp static library
target_link_directories(MySharedLibrary PRIVATE ${STATIC_LIB_PATH})
target_link_libraries(MySharedLibrary PRIVATE ${STATIC_LIB_NAME})
