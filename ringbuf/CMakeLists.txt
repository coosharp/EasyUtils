cmake_minimum_required(VERSION 3.10)

project(uRingbuf C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add source files
set(URINGBUF_SOURCES
    uRingbuf.c
)

set(URINGBUF_HEADERS
    uRingbuf.h
)

# Create static library
add_library(uringbuf_lib STATIC ${URINGBUF_SOURCES})

# Set library properties
set_target_properties(uringbuf_lib PROPERTIES
    PUBLIC_HEADER "${URINGBUF_HEADERS}"
    VERSION 1.0.0
    SOVERSION 1
)

# Create executable for testing
add_executable(test test.c)

# Link the library to the test executable
target_link_libraries(test uringbuf_lib)

# Optional: Install targets
install(TARGETS uringbuf_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS test
    RUNTIME DESTINATION bin
)
