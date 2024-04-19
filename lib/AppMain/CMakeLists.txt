cmake_minimum_required(VERSION 3.22)

set(AppMainSrc "${CMAKE_CURRENT_SOURCE_DIR}/src/app_main.c")
set(AppMainHead "${CMAKE_CURRENT_SOURCE_DIR}/head")

add_library(
    AppMain
    "${AppMainSrc}"
)
target_include_directories(
    AppMain
    PRIVATE
    "${AppMainHead}"
)
target_link_libraries(
    AppMain
    St_Interface
    FreeRtos
    ${PROJECT_NAME}_libs
)

Add_Components(AppMain AppMainHead)