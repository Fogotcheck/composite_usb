cmake_minimum_required(VERSION 3.22)

set(St_DriversPath
    "${CMAKE_SOURCE_DIR}/St_CubeHal/Drivers"
)

add_library(St_Interface INTERFACE)

target_include_directories(St_Interface
    SYSTEM INTERFACE
    "${St_DriversPath}/CMSIS/Device/ST/STM32WBxx/Include"
    "${St_DriversPath}/CMSIS/Include"
    "${St_DriversPath}/STM32WBxx_HAL_Driver/Inc"
    "${St_DriversPath}/STM32WBxx_HAL_Driver/Inc/Legacy"
    "${CMAKE_SOURCE_DIR}/St_CubeHal/Core/Inc"
)

file(GLOB_RECURSE ST_DriversSRC
    "${St_DriversPath}/STM32WBxx_HAL_Driver/Src/*.c"
)

add_library(St_Drivers
    "${ST_DriversSRC}"
    "${CMAKE_SOURCE_DIR}/St_CubeHal/Core/Src/system_stm32wbxx.c"
)

target_link_libraries(St_Drivers St_Interface)
target_link_libraries(St_Interface INTERFACE St_Drivers)