
cmake_minimum_required(VERSION 2.8.8)

# This will define the name of the solution file in the build directory
project(t2bc_ffi)

include(CheckIncludeFiles)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(CMAKE_REQUIRED_INCLUDES ${LLVM_INCLUDE_DIRS})

# Define our shared library
add_library(t2bc SHARED assembler.cpp)

# Find the libraries that correspond to the LLVM components
# that we wish to use.
llvm_map_components_to_libnames(llvm_libs all)

# Link against LLVM libraries
target_link_libraries(t2bc ${llvm_libs})
