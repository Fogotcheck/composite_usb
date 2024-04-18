cmake_minimum_required(VERSION 3.22)

if(OPENOCD_ENABLE)
    include("${CMAKE_SOURCE_DIR}/cmake/utils/OpenOCD.cmake")
endif()

if(ENVIRONMENT_VSCODE)
    include("${CMAKE_SOURCE_DIR}/cmake/utils/VScode.cmake")
endif()

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "ARM" AND
    CMAKE_SYSTEM_NAME STREQUAL "Generic")
    include("${CMAKE_SOURCE_DIR}/cmake/utils/PostBuild.cmake")
endif()
