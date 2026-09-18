cmake_minimum_required(VERSION 3.10)

project(u_queue C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(U_QUEUE_SOURCES
    u_queue.c
)

set(U_QUEUE_HEADERS
    u_queue.h
)

add_library(uqueue_lib STATIC ${U_QUEUE_SOURCES})

target_include_directories(uqueue_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(uqueue_lib PROPERTIES
    PUBLIC_HEADER "${U_QUEUE_HEADERS}"
    VERSION 1.0.0
    SOVERSION 1
)

add_executable(queue_test test.c)
target_link_libraries(queue_test PRIVATE uqueue_lib)

install(TARGETS uqueue_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS queue_test
    RUNTIME DESTINATION bin
)
