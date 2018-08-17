# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

jfc_project(library
    NAME "gdkmemory"
    VERSION 0.0
    DESCRIPTION "game development kit data structures"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

    SOURCE_LIST 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/delete_me.cpp # jfc_project has to be modified to handle TYPE HEADER_ONLY
)
