cmake_minimum_required(VERSION 3.10)

project(u_log C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(U_LOG_SOURCES
    u_log.c
)

set(U_LOG_HEADERS
    u_log.h
)

add_library(ulog_lib STATIC ${U_LOG_SOURCES})

target_include_directories(ulog_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(ulog_lib PROPERTIES
    PUBLIC_HEADER "${U_LOG_HEADERS}"
    VERSION 1.0.0
    SOVERSION 1
)

add_executable(log_test test.c)
target_link_libraries(log_test PRIVATE ulog_lib)

install(TARGETS ulog_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS log_test
    RUNTIME DESTINATION bin
)
