# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

jfc_project(library
    NAME "gdkinput"
    VERSION 0.0
    DESCRIPTION "game development kit HID lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

        ${gdkmath_INCLUDE_DIRECTORIES}

        ${glfw_INCLUDE_DIR}

    SOURCE_LIST
        #${CMAKE_CURRENT_SOURCE_DIR}/src/gamepads.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/keyboard.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mouse.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/input_protected.cpp

    LIBRARIES
        ${glfw_LIBRARIES}

    DEPENDENCIES
        "glfw"
)

if(JFC_BUILD_TESTS)
    if(NOT CMAKE_SYSTEM_NAME MATCHES "Emscripten")
        jfc_add_tests(
            C++_STANDARD 17
            C_STANDARD 90

            TEST_SOURCE_FILES
                ${CMAKE_CURRENT_LIST_DIR}/test/resources_test.cpp

            INCLUDE_DIRECTORIES
                ${gdkresources_INCLUDE_DIRECTORIES}

            LIBRARIES
                ${gdkresources_LIBRARIES}

            DEPENDENCIES
                "gdkinput"
        )
    else()
        jfc_log(STATUS "test" "testing not supported on ${CMAKE_SYSTEM_NAME}. Skipping...")
    endif()
endif()
