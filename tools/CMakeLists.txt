if (${TARGET} STREQUAL "linux" OR {TARGET} STREQUAL "windows")
  add_subdirectory(pioasm)
  add_subdirectory(elf2uf2)
endif()