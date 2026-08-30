cmake_minimum_required(VERSION 3.10)
project(EasyUtils C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add source files
set(SOURCES
    uMailbox.c
    test.c
)

# Create executable
add_executable(test ${SOURCES})

# Link libraries if needed
# target_link_libraries(test)
