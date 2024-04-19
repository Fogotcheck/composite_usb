cmake_minimum_required(VERSION 3.22)
include("${CMAKE_SOURCE_DIR}/cmake/interface/Components.cmake")

add_subdirectory(rtos)
add_subdirectory(AppMain)
add_subdirectory(Debug)

target_link_libraries(
    ${PROJECT_NAME}
    ${PROJECT_NAME}_libs
    FreeRtos
)