cmake_minimum_required(VERSION 3.22)

set(ModuleName "FMConf")
set(${ModuleName}Src
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/${ModuleName}.c"
)
set(${ModuleName}PubHead
    "${CMAKE_CURRENT_SOURCE_DIR}/Inc"
)
set(${ModuleName}PrivHead
    "${CMAKE_CURRENT_SOURCE_DIR}/Config"
)
set(${ModuleName}Conf
    "${${ModuleName}PrivHead}/${ModuleName}.txt"
)
set(${ModuleName}ConfObj
    "${CMAKE_CURRENT_BINARY_DIR}/${ModuleName}_conf_bin.o"
)

add_custom_command(
    OUTPUT ${${ModuleName}ConfObj}
    COMMAND ${CMAKE_OBJCOPY} --input-target=binary --output-target=elf32-littlearm --binary-architecture=arm ${${ModuleName}Conf} ${${ModuleName}ConfObj}
    DEPENDS ${${ModuleName}Conf}
)

add_library(${ModuleName} ${${ModuleName}Src} ${${ModuleName}ConfObj})

target_link_libraries(${ModuleName}
    St_Interface
    FreeRtos
)

target_include_directories(${ModuleName}
    PRIVATE
    "${${ModuleName}PubHead}"
    "${${ModuleName}PrivHead}"
)

string(REGEX REPLACE "[/:.]" "_" ${ModuleName}Conf ${${ModuleName}Conf})

target_compile_definitions(
    ${ModuleName}
    PRIVATE
    __BINARY_PATH="${${ModuleName}Conf}"
)

Add_Components(${ModuleName} ${ModuleName}PubHead)
