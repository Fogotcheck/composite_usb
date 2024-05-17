cmake_minimum_required(VERSION 3.22)

set(ModuleName "BProt")
set(${ModuleName}Src
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/${ModuleName}.c"
)
set(${ModuleName}PubHead
    "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
)
set(${ModuleName}PrivHead
    "${CMAKE_CURRENT_SOURCE_DIR}/Config"
)

add_library(BPInterface INTERFACE)

target_include_directories(
    BPInterface
    SYSTEM INTERFACE
    "${${ModuleName}PubHead}"
    "${${ModuleName}PrivHead}"
)
add_subdirectory(Crc)
add_subdirectory(VRegs)
add_subdirectory(CdcPort)
add_library(${ModuleName} ${${ModuleName}Src})

target_link_libraries(${ModuleName}
    BPInterface
    FreeRtos
    Debug_Print
)

target_include_directories(${ModuleName}
    PRIVATE
    "${${ModuleName}PubHead}"
    "${${ModuleName}PrivHead}"
)

Add_Components(${ModuleName} ${ModuleName}PubHead)