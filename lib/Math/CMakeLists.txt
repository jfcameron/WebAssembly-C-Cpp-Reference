# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

jfc_project(library
    NAME "gdkmath"
    VERSION 0.0
    DESCRIPTION "game development kit math lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        
    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

        ${glm_INCLUDE_DIR}
        ${nlohmann_INCLUDE_DIR}

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/intvector2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mat4x4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector4.cpp
)

#[[if(NOT CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    jfc_add_tests(
        C++_STANDARD 17
        C_STANDARD 90

        TEST_SOURCE_FILES
            ${CMAKE_CURRENT_LIST_DIR}/test/example_test.cpp
    )
else()
    jfc_log(STATUS "test" "testing not supported on ${CMAKE_SYSTEM_NAME}. Skipping...")
endif()]]
