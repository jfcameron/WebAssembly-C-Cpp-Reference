# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

jfc_project(library
    NAME "gdktime"
    VERSION 0.0
    DESCRIPTION "game development kit time lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

        ${gdkglfwwrapper_INCLUDE_DIRECTORIES}
        ${gdkmath_INCLUDE_DIRECTORIES}

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/time.cpp

)
