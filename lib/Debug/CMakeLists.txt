cmake_minimum_required(VERSION 3.22)

set(Debug_Src "${CMAKE_CURRENT_SOURCE_DIR}/src/Debug_Print.c")
set(Debug_Private_Heads
    "${CMAKE_CURRENT_SOURCE_DIR}/config"
)
set(Debug_Public_Heads
    "${CMAKE_CURRENT_SOURCE_DIR}/head"
)

add_library(Debug_Print ${Debug_Src})
target_link_libraries(Debug_Print St_Interface)

target_include_directories(Debug_Print PRIVATE
    "${Debug_Private_Heads}"
    "${Debug_Public_Heads}"
)

Add_Components(Debug_Print Debug_Public_Heads)
