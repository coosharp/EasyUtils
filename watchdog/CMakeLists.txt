cmake_minimum_required(VERSION 3.10)

project(uWatchdog C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add source files
set(UWATCHDOG_SOURCES
    uWatchdog.c
)

set(UWATCHDOG_HEADERS
    uWatchdog.h
)

# Create static library
add_library(uwatchdog_lib STATIC ${UWATCHDOG_SOURCES})

# Set library properties
set_target_properties(uwatchdog_lib PROPERTIES
    PUBLIC_HEADER "${UWATCHDOG_HEADERS}"
    VERSION 1.0.0
    SOVERSION 1
)

# Create executable for testing
add_executable(test test.c)

# Link the library to the test executable
target_link_libraries(test uwatchdog_lib)

# Optional: Install targets
install(TARGETS uwatchdog_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(TARGETS test
    RUNTIME DESTINATION bin
)
