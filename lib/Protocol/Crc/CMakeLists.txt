cmake_minimum_required(VERSION 3.22)

set(crcSrc
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/crc.c"
)
set(crcPubHead
    "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
)

target_include_directories(
    BPInterface
    SYSTEM INTERFACE
    "${crcPubHead}"
)

add_library(crc ${crcSrc})

target_link_libraries(
    crc
    BPInterface
)

target_link_libraries(
    BPInterface
    INTERFACE
    crc
)
