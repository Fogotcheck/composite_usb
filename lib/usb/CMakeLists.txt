cmake_minimum_required(VERSION 3.22)

add_library(tinyusb_config INTERFACE)

set(TinyUsbPath "${CMAKE_CURRENT_SOURCE_DIR}/TinyUsb")

target_compile_definitions(
    tinyusb_config
    INTERFACE
    "CFG_TUSB_MCU=OPT_MCU_STM32WB"
)

target_include_directories(
    tinyusb_config
    SYSTEM INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/tini_conf"
)

target_link_libraries(
    tinyusb_config
    INTERFACE
    St_Interface
)

add_subdirectory(
    "${TinyUsbPath}/src"
)
