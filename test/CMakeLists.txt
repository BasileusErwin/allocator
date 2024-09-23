include(CTest)
find_library(CHECK_LIBRARY check)

enable_testing()

file(GLOB TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/*.c)

include_directories(${ALLOCATOR_INCLUDES})

add_executable(test ${TEST_SOURCES})
target_compile_options(test PRIVATE -g)
target_link_libraries(test PRIVATE check)
target_link_libraries(test PRIVATE allocator_lib)

add_test(NAME test COMMAND test)
