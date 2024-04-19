cmake_minimum_required(VERSION 3.22)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME} ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME} ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJDUMP} -S ${PROJECT_NAME} > ${PROJECT_NAME}.S
    COMMAND ${CMAKE_NM} -a -l -S -s ${PROJECT_NAME} > ${PROJECT_NAME}.map
)

if(CMAKE_SIZE)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_SIZE} -A ${PROJECT_NAME}
        COMMAND ${CMAKE_NM} -A -S -t d -s --size-sort --print-size ${PROJECT_NAME} > FuctionSizeInfo.map
        COMMAND echo "Build - success"
        COMMAND echo "CMAKE_BUILD_TYPE::${CMAKE_BUILD_TYPE}"
    )
endif()

add_custom_target(InstallProject
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
    COMMENT "Installing ${PROJECT_NAME}"
)
