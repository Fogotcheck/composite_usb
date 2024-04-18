cmake_minimum_required(VERSION 3.22)

set(StCorePath "${CMAKE_CURRENT_SOURCE_DIR}/Core")

include("${CMAKE_SOURCE_DIR}/cmake/interface/StHal.cmake")

target_link_libraries(${PROJECT_NAME} St_Interface)

target_sources(${PROJECT_NAME} PRIVATE
    "${StCorePath}/Src/main.c"
    "${StCorePath}/Src/stm32wbxx_hal_msp.c"
    "${StCorePath}/Src/stm32wbxx_it.c"
    "${StCorePath}/Src/syscalls.c"
    "${StCorePath}/Src/sysmem.c"
    "${StCorePath}/Startup/startup_stm32wb55rgvx.s"
)
