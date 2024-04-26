cmake_minimum_required(VERSION 3.22)

set(CompositeUSBSrc "${CMAKE_CURRENT_SOURCE_DIR}/src/CompositeUsb.c")
set(CompositeUSBHeads
    "${CMAKE_CURRENT_SOURCE_DIR}/head"
    "${CMAKE_CURRENT_SOURCE_DIR}/ReportTypes"
)

add_library(CompositeUSB ${CompositeUSBSrc})
target_link_libraries(CompositeUSB
    St_Interface
    # St_Usb don't work
    tinyusb
    FreeRtos
    Debug_Print
)

target_include_directories(CompositeUSB PRIVATE
    "${CompositeUSBHeads}"
)

Add_Components(CompositeUSB CompositeUSBHeads)