cmake_minimum_required(VERSION 3.20)
project(allocator)

set(CMAKE_C_STANDARD 11)

set(ALLOCATOR_INCLUDES ${PROJECT_SOURCE_DIR}/src/includes)
set(ALLOCATOR_SOURCES ${PROJECT_SOURCE_DIR}/src)

# Executable
include_directories(${ALLOCATOR_INCLUDES})
add_compile_options(-Wall -pedantic)
file(GLOB ALLOCATOR_SOURCES ${ALLOCATOR_SOURCES}/*.c)
add_executable(allocator ${ALLOCATOR_SOURCES})
install(TARGETS allocator DESTINATION bin)

# Debug

set(CMAKE_BUILD_TYPE Debug)

add_executable(allocator-debug ${ALLOCATOR_SOURCES})
target_compile_options(allocator-debug PRIVATE -g)

# Library

file(GLOB ALLOCATOR_SOURCES ${ALLOCATOR_SOURCES}/*.c)
add_library(allocator_lib ${ALLOCATOR_SOURCES})
include_directories(${ALLOCATOR_INCLUDES})

install(TARGETS allocator_lib DESTINATION lib)
install(DIRECTORY ${ALLOCATOR_INCLUDES}
    DESTINATION include/allocator
    FILES_MATCHING PATTERN "*.h")

# Test

add_subdirectory(test)
