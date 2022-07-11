set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m0)

set(MCPU_FLAGS "-mthumb -mcpu=cortex-m0plus")
set(VFP_FLAGS "")
set(LD_FLAGS "-nostartfiles --specs=nano.specs --specs=nosys.specs")

# If BOARD_LINKER_FILE is defined use as linker script
if(DEFINED BOARD_LINKER_FILE)
	set(LD_FLAGS "${LD_FLAGS} -T ${PROJECT_SOURCE_DIR}/linker/${BOARD_LINKER_FILE}")
endif()

include(${CMAKE_CURRENT_LIST_DIR}/common/arm-none-eabi.cmake)