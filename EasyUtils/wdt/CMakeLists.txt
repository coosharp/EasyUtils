cmake_minimum_required(VERSION 3.10)

project(u_wdt C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(UWDT_SOURCES
    u_wdt.c
)

set(UWDT_HEADERS
    u_wdt.h
)

add_library(uwdt_lib STATIC ${UWDT_SOURCES})

target_include_directories(uwdt_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(uwdt_lib PROPERTIES
    PUBLIC_HEADER "${UWDT_HEADERS}"
    VERSION 1.0.0
    SOVERSION 1
)

add_executable(wdt_test test.c)
target_link_libraries(wdt_test PRIVATE uwdt_lib)

install(TARGETS uwdt_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS wdt_test
    RUNTIME DESTINATION bin
)
