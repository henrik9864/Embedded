cmake_minimum_required(VERSION 3.20)

project(ecs)

add_library(${PROJECT_NAME} STATIC src/ecs.cpp)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)