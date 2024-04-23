cmake_minimum_required(VERSION 3.22)

set(VComPortSrc "${CMAKE_CURRENT_SOURCE_DIR}/src/VirtComPort.c")
set(VComPortHeads
    "${CMAKE_CURRENT_SOURCE_DIR}/head"
)

add_library(VComPort ${VComPortSrc})
target_link_libraries(VComPort
    St_Interface
    # St_Usb don't work
    FreeRtos
)

target_include_directories(VComPort PRIVATE
    "${VComPortHeads}"
)

Add_Components(VComPort VComPortHeads)