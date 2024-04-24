cmake_minimum_required(VERSION 3.22)
include("${CMAKE_SOURCE_DIR}/cmake/interface/Components.cmake")

add_subdirectory(rtos)
add_subdirectory(Debug)
add_subdirectory(usb)
add_subdirectory(CompositeUsb)

target_link_libraries(
    ${PROJECT_NAME}
    ${PROJECT_NAME}_libs
    FreeRtos
)