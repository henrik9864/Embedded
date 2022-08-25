cmake_minimum_required(VERSION 3.20)

project(main CXX ASM C)

add_executable(${PROJECT_NAME} src/main.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

add_custom_command(
    OUTPUT  inc/pio/ws2812.hpp          # Treated as relative to CMAKE_CURRENT_BINARY_DIR
    COMMAND pioasm -o c -p pio_0_mem ${CMAKE_CURRENT_SOURCE_DIR}/src/pio/ws2812.pio ${CMAKE_CURRENT_BINARY_DIR}/inc/pio/ws2812.hpp
    DEPENDS src/pio/ws2812.pio  # Treated as relative to CMAKE_CURRENT_SOURCE_DIR
)

add_library(pioss INTERFACE inc/pio/ws2812.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE pico etl::etl)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc)

set_target_properties(main PROPERTIES SUFFIX ".elf")

add_custom_target(main ALL DEPENDS src/pio/ws2812.pio)

add_custom_command(
    COMMAND pioasm -o c -p pio_0 src/pio/ws2812.pio src/pio/ws2812.h
    DEPENDS src/pio/ws2812.pio src/pio/ws2812.h
    OUTPUTS src/pio/ws2812.h
    COMMENT "Generating PIO header files."
)