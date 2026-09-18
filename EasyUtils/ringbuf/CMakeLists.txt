cmake_minimum_required(VERSION 3.10)

project(u_ringbuf C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(URINGBUF_SOURCES
    u_ringbuf.c
)

set(URINGBUF_HEADERS
    u_ringbuf.h
)

add_library(uringbuf_lib STATIC ${URINGBUF_SOURCES})

target_include_directories(uringbuf_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(uringbuf_lib PROPERTIES
    PUBLIC_HEADER "${URINGBUF_HEADERS}"
    VERSION 1.0.0
    SOVERSION 1
)

add_executable(ringbuf_test test.c)
target_link_libraries(ringbuf_test PRIVATE uringbuf_lib)

install(TARGETS uringbuf_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS ringbuf_test
    RUNTIME DESTINATION bin
)
