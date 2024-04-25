cmake_minimum_required(VERSION 3.22)

add_library(tinyusb_config INTERFACE)

set(TinyUsbPath "${CMAKE_CURRENT_SOURCE_DIR}/TinyUsb")

target_compile_definitions(
    tinyusb_config
    INTERFACE
    "CFG_TUSB_MCU=OPT_MCU_STM32WB"
    # "CFG_TUSB_DEBUG=3"
    # "CFG_TUSB_OS=OPT_OS_FREERTOS" don't work
)

target_include_directories(
    tinyusb_config
    SYSTEM INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/tini_conf"
    "${TinyUsbPath}/src/portable/st/stm32_fsdev"
    "${TinyUsbPath}/hw"
)

target_link_libraries(
    tinyusb_config
    INTERFACE
    St_Interface
    # FreeRtos 

)

add_subdirectory(
    "${TinyUsbPath}/src"
)

add_library(
    TinyPort
    "${TinyUsbPath}/src/portable/st/stm32_fsdev/dcd_stm32_fsdev.c"
    "${TinyUsbPath}/src/portable/st/typec/typec_stm32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/tiny_descr/usb_descriptors.c"
)

target_link_libraries(
    TinyPort
    tinyusb_config
    tinyusb
)

target_link_libraries(
    tinyusb
    INTERFACE
    TinyPort
)