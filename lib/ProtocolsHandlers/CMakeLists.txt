cmake_minimum_required(VERSION 3.22)

set(ModuleName "BPHandlers")

set(${ModuleName}Src
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/${ModuleName}.c"
)
set(${ModuleName}PubHead
    "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
)

add_library(${ModuleName} ${${ModuleName}Src})

target_link_libraries(${ModuleName}
    St_Interface
    FreeRtos
    ${PROJECT_NAME}_libs
)

Add_Components(${ModuleName} ${ModuleName}PubHead)