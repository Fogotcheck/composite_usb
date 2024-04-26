cmake_minimum_required(VERSION 3.22)

add_library(${PROJECT_NAME}_libs INTERFACE)

function(Add_Warnings COMPONENT)
    target_compile_options(${COMPONENT} PRIVATE
        -Wall
        -Wextra
        -Werror
        -Wfatal-errors
        -Wdouble-promotion
        -Wstrict-prototypes
        -Wstrict-overflow
        -Werror-implicit-function-declaration
        -Wfloat-equal
        -Wundef
        -Wshadow
        -Wwrite-strings
        -Wsign-compare
        -Wmissing-format-attribute
        -Wunreachable-code
        -Wcast-align
        -Wcast-function-type
        -Wcast-qual
        -Wnull-dereference
        -Wuninitialized
        -Wunused
        -Wunused-function
        -Wreturn-type
        -Wredundant-decls
    )
endfunction(Add_Warnings COMPONENT)

function(Add_Components COMPONENT COMPONENT_HEADS)
    Add_Warnings(${COMPONENT})
    target_link_libraries(${PROJECT_NAME}_libs INTERFACE ${COMPONENT})

    foreach(X IN LISTS ${COMPONENT_HEADS})
        target_include_directories(${PROJECT_NAME}_libs SYSTEM INTERFACE ${X})
    endforeach(X IN LISTS COMPONENT_HEADS)
endfunction(Add_Components COMPONENT HEADS)