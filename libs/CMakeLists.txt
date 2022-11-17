add_subdirectory(xecs)
add_subdirectory(utilities)
add_subdirectory(hal)

if (${TARGET} STREQUAL "embedded")
  add_subdirectory(bsp/rp2040)
  add_subdirectory(drivers)
  add_subdirectory(etl)
endif()