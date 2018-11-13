# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

jfc_project(library
    NAME "gdkglfwwrapper"
    VERSION 0.0
    DESCRIPTION "simplified cpp api to the glfw3 library"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        ${glfw_INCLUDE_DIR}

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

    SOURCE_LIST 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/simpleglfwwindow.cpp

    LIBRARIES
        ${glfw_LIBRARIES}

    DEPENDENCIES
        "glfw"
)
