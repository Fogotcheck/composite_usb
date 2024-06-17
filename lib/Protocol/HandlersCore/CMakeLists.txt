cmake_minimum_required(VERSION 3.22)

set(HandlersCoreSrc
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/HandlersCore.c"
)
set(HandlersCoreHead
    "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
)

target_include_directories(
    BPInterface
    SYSTEM INTERFACE
    ${HandlersCoreHead}
)

add_library(HandlersCore
    ${HandlersCoreSrc}
)

target_link_libraries(
    HandlersCore
    BPInterface
)

target_link_libraries(
    BPInterface
    INTERFACE
    HandlersCore
)