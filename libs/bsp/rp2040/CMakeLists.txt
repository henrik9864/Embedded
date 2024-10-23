cmake_minimum_required(VERSION 3.20)

project(rp2040 ASM CXX)

set_property(SOURCE w25q080.s APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)
set_property(SOURCE wait_ssi_ready.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)
set_property(SOURCE read_flash_sreg.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)
set_property(SOURCE exit_from_boot2.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)
set_property(SOURCE asm_helper.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp -c" CACHE STRING "" FORCE)

add_library(${PROJECT_NAME} OBJECT src/boot2/w25q080.s src/startup.cpp "src/vtable.cpp" "src/rp2040/rp2040.cpp" "src/rp2040/rp2040_regs.cpp" "src/rp2040/rp2040_pins.cpp" "src/rp2040/rp2040_pwm.cpp" "src/rp2040/rp2040_uart.cpp" "src/rp2040/rp2040_spi.cpp" "src/rp2040/rp2040_clock.cpp" "src/rp2040/rp2040_dma.cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE hal)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)