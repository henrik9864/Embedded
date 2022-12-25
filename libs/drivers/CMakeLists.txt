cmake_minimum_required(VERSION 3.20)

project(drivers)

add_library(${PROJECT_NAME} STATIC src/ln298n.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(${PROJECT_NAME} PRIVATE hal)