cmake_minimum_required(VERSION 3.22)

set(BPCdcPortSrc
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/BPCDCport.c"
)
set(BPCdcPortPubHead
    "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
)

target_include_directories(
    BPInterface
    SYSTEM INTERFACE
    ${BPCdcPortPubHead}
)

add_library(BPCdcPort ${BPCdcPortSrc})

target_link_libraries(
    BPCdcPort
    BPInterface
    CompositeUSB
)

target_link_libraries(
    CompositeUSB
    BPCdcPort
    BPInterface
)

target_link_libraries(
    BPInterface
    INTERFACE
    BPCdcPort
)