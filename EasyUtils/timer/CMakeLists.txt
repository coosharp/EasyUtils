cmake_minimum_required(VERSION 3.10)

project(u_timer C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(UTIMER_SOURCES
    u_timer.c
)

set(UTIMER_HEADERS
    u_timer.h
)

add_library(utimer_lib STATIC ${UTIMER_SOURCES})

target_include_directories(utimer_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(utimer_lib PROPERTIES
    PUBLIC_HEADER "${UTIMER_HEADERS}"
    VERSION 1.0.0
    SOVERSION 1
)

add_executable(timer_test test.c)
target_link_libraries(timer_test PRIVATE utimer_lib)

install(TARGETS utimer_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS timer_test
    RUNTIME DESTINATION bin
)
