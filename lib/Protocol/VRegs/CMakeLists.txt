cmake_minimum_required(VERSION 3.22)

set(VRegSrc
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/VReg.c"
)
set(VRegPubHead
    "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
)

target_include_directories(
    BPInterface
    SYSTEM INTERFACE
    ${VRegPubHead}
)

add_library(VReg ${VRegSrc})

target_link_libraries(
    VReg
    BPInterface
)

target_link_libraries(
    BPInterface
    INTERFACE
    VReg
)