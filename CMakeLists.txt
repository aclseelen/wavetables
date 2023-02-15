cmake_minimum_required(VERSION 3.24)
project(wavetables C)

set(CMAKE_C_STANDARD 23)

add_executable(wavetables main.c wavetables.h file_handling.c math.c)
include_directories()
target_link_libraries(wavetables PRIVATE m)

enable_testing()
add_subdirectory(test/ctest)