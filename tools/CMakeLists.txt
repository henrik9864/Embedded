if (${TARGET} STREQUAL "linux")
  add_subdirectory(pioasm)
  add_subdirectory(elf2uf2)
endif()