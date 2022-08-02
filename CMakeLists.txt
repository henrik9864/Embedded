cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# note: this must happen before project()
#include("${PICO_SDK_PATH}/external/pico_sdk_import.cmake")

#pico_sdk_init()

project(EnCS NONE)

add_subdirectory(libs)
add_subdirectory(apps)