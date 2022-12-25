cmake_minimum_required(VERSION 3.20)

function(generate_pio_headers project)
  #add_library(lib123 INTERFACE)
  foreach(arg IN ITEMS ${ARGN})
     get_filename_component(item_path ${arg} DIRECTORY)
     get_filename_component(item_we ${arg} NAME_WE)

     add_custom_command(
      OUTPUT  ${item_path}/${item_we}.hpp  # Treated as relative to CMAKE_CURRENT_BINARY_DIR
      COMMAND pioasm -o c -p pio_0_mem ${CMAKE_CURRENT_SOURCE_DIR}/${item_path}/${item_we}.pio ${CMAKE_CURRENT_BINARY_DIR}/${item_path}/${item_we}.hpp
      DEPENDS ${item_path}/${item_we}.pio  # Treated as relative to CMAKE_CURRENT_SOURCE_DIR
     )

     #target_sources(lib123 INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/${item_path}/${item_we}.hpp)
     add_library(${project} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/${item_path}/${item_we}.hpp)
  endforeach()
endfunction()

add_custom_command(
  OUTPUT  inc/pio/blink.hpp  # Treated as relative to CMAKE_CURRENT_BINARY_DIR
  COMMAND pioasm -o c -p pio_0_mem ${CMAKE_CURRENT_SOURCE_DIR}/src/pio/blink.pio ${CMAKE_CURRENT_BINARY_DIR}/inc/pio/blink.hpp
  DEPENDS src/pio/blink.pio  # Treated as relative to CMAKE_CURRENT_SOURCE_DIR
)

project(main CXX ASM C)

add_executable(${PROJECT_NAME} src/main.cpp src/experiments/stepper.cpp src/experiments/pio.cpp src/experiments/pwm.cpp src/experiments/i2c.cpp inc/pio/blink.hpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

target_link_libraries(${PROJECT_NAME} PRIVATE rp2040 hal)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/inc)

#generate_pio_headers(main src/pio/ws2812.pio)

set_target_properties(main PROPERTIES SUFFIX ".elf")