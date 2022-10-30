add_subdirectory(xecs)
add_subdirectory(ecs)
add_subdirectory(utilities)

if (${TARGET} STREQUAL "embedded")
  add_subdirectory(pico)
  add_subdirectory(etl)
endif()