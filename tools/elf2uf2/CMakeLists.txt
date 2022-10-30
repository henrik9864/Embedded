cmake_minimum_required(VERSION 3.20)

project(elf2uf2 CXX C)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)