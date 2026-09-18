cmake_minimum_required(VERSION 3.10)

project(u_shell C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(U_SHELL_SOURCES
    u_shell.c
)

set(U_SHELL_HEADERS
    u_shell.h
)

add_library(ushell_lib STATIC ${U_SHELL_SOURCES})

target_include_directories(ushell_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(ushell_lib PROPERTIES
    PUBLIC_HEADER "${U_SHELL_HEADERS}"
    VERSION 1.0.0
    SOVERSION 1
)

add_executable(shell_test test.c)
target_link_libraries(shell_test PRIVATE ushell_lib)

install(TARGETS ushell_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS shell_test
    RUNTIME DESTINATION bin
)
