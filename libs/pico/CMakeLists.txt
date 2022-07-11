cmake_minimum_required(VERSION 3.20)

project(pico ASM CXX)

set_property(SOURCE w25q080.s APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)
set_property(SOURCE wait_ssi_ready.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)
set_property(SOURCE read_flash_sreg.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)
set_property(SOURCE exit_from_boot2.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)
set_property(SOURCE asm_helper.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)

add_library(${PROJECT_NAME} OBJECT src/boot2/w25q080.s src/startup.cpp src/vtable.cpp)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)