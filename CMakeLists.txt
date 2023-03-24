cmake_minimum_required(VERSION 3.22)
project(wavetables VERSION 0.1.0 DESCRIPTION "Generates, analyzes, and edits wave tables" LANGUAGES C)

set(CMAKE_C_STANDARD 23)

add_executable(wavetables main.c wavetables.h file_handling.c fourier.c waveforms.c operations.c helper.c)
include_directories()
target_link_libraries(wavetables PRIVATE m)
