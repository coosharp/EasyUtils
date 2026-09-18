cmake_minimum_required(VERSION 3.10)

project(u_ll C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(U_LL_SOURCES
    u_ll.c
)

set(U_LL_HEADERS
    u_ll.h
)

add_library(ullib STATIC ${U_LL_SOURCES})

target_include_directories(ullib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(ullib PROPERTIES
    PUBLIC_HEADER "${U_LL_HEADERS}"
    VERSION 1.0.0
    SOVERSION 1
)

add_executable(ll_test test.c)
target_link_libraries(ll_test PRIVATE ullib)

install(TARGETS ullib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS ll_test
    RUNTIME DESTINATION bin
)
