cmake_minimum_required(VERSION 3.22)

option(OPENOCD_ENABLE "Custom target openocd flash" OFF)
option(ENVIRONMENT_VSCODE "Custom target make json for vsCode" OFF)

project(composite_usb VERSION 0.1.0 LANGUAGES C ASM)

set(MCU_DEVICE "STM32WB55xx")
set(USB_OPTS "CFG_TUSB_MCU=OPT_MCU_STM32WB")
add_compile_definitions(
    ${MCU_DEVICE}
    "USE_HAL_DRIVER"
    "__NEWLIB__"
    "USE_FreeRTOS"
    # "configRECORD_STACK_HIGH_ADDRESS=1" # stack trace
)
add_link_options(
    "-T${CMAKE_SOURCE_DIR}/St_CubeHal/STM32WB55RGVX_FLASH.ld"
)

add_executable(${PROJECT_NAME})
target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)
add_subdirectory(St_CubeHal)
add_subdirectory(lib)
add_subdirectory(AppMain)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin DESTINATION ${CMAKE_BINARY_DIR}/bin)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.hex DESTINATION ${CMAKE_BINARY_DIR}/bin)
include("${CMAKE_SOURCE_DIR}/cmake/utils/Opts.cmake")
