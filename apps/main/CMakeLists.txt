cmake_minimum_required(VERSION 3.20)

project(main CXX ASM C)

set_property(SOURCE w25q080.s APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp" CACHE STRING "" FORCE)
set_property(SOURCE wait_ssi_ready.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp" CACHE STRING "" FORCE)
set_property(SOURCE read_flash_sreg.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp" CACHE STRING "" FORCE)
set_property(SOURCE exit_from_boot2.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp" CACHE STRING "" FORCE)
set_property(SOURCE asm_helper.S APPEND PROPERTY COMPILE_OPTIONS "-x assembler-with-cpp" CACHE STRING "" FORCE)

add_executable(${PROJECT_NAME} boot2/w25q080.s startup/startup.cpp startup/vtable.cpp src/main.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

#target_link_libraries(${PROJECT_NAME} ecs)
#target_sources(${PROJECT_NAME} ecs)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)