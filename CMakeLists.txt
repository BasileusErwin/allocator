cmake_minimum_required(VERSION 3.20)
project(allocator)

set(CMAKE_C_STANDARD 11)

set(ALLOCATOR_INCLUDES ${PROJECT_SOURCE_DIR}/src/includes)
set(ALLOCATOR_SOURCES ${PROJECT_SOURCE_DIR}/src)

include_directories(${ALLOCATOR_INCLUDES})

add_compile_options(-Wall -pedantic)

file(GLOB ALLOCATOR_SOURCES ${ALLOCATOR_SOURCES}/*.c)

add_executable(allocator ${ALLOCATOR_SOURCES})


# Debug

set(CMAKE_BUILD_TYPE Debug)

add_executable(allocator-debug ${ALLOCATOR_SOURCES})
target_compile_options(allocator-debug PRIVATE -g)
