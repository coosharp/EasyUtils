cmake_minimum_required(VERSION 3.10)

project(uMessage VERSION 0.1.0 LANGUAGES C)

# Options
option(BUILD_TESTS "Build test executable" ON)
# If user wants shared library instead of static, set -DBUILD_SHARED_LIBS=ON
# option(BUILD_SHARED_LIBS "Build uMessage as shared library" OFF)

# Library
add_library(uMessage
    uMessage.c
)

# Public include dir for consumers and for installation
target_include_directories(uMessage
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# Target properties (C standard set on target)
set_target_properties(uMessage PROPERTIES
    C_STANDARD 99
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    PUBLIC_HEADER "uMessage.h"
)

# Test executable (optional)
if (BUILD_TESTS)
    add_executable(test_message test.c)
    target_link_libraries(test_message
        PRIVATE
            uMessage
    )
endif()

# Installation rules
include(GNUInstallDirs)

install(TARGETS uMessage
    EXPORT uMessageTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES uMessage.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT uMessageTargets
    FILE uMessageTargets.cmake
    NAMESPACE uMessage::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/uMessage
)

export(PACKAGE uMessage)