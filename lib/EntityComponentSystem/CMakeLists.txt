# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

jfc_project(library
    NAME "gdkentitycomponentsystem"
    VERSION 0.0
    DESCRIPTION "an entity component system lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

        ${gdkmath_INCLUDE_DIRECTORIES}

        ${nlohmann_INCLUDE_DIR}

    SOURCE_LIST 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/component.cpp
    	${CMAKE_CURRENT_SOURCE_DIR}/src/entity.cpp
    	${CMAKE_CURRENT_SOURCE_DIR}/src/scene.cpp
    	${CMAKE_CURRENT_SOURCE_DIR}/src/scenegraph.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/src/scenemanager.cpp

    LIBRARIES
        ${gdkmath_LIBRARIES}
)

if(JFC_BUILD_TESTS)
    if(NOT CMAKE_SYSTEM_NAME MATCHES "Emscripten")
        jfc_add_tests(
            C++_STANDARD 17
            C_STANDARD 90

            TEST_SOURCE_FILES
                ${CMAKE_CURRENT_LIST_DIR}/test/example_test.cpp

            INCLUDE_DIRECTORIES
                ${gdkentitycomponentsystem_INCLUDE_DIRECTORIES}

            LIBRARIES
                ${gdkentitycomponentsystem_LIBRARIES}

            DEPENDENCIES
                "gdkentitycomponentsystem"
        )
    else()
        jfc_log(STATUS "test" "testing not supported on ${CMAKE_SYSTEM_NAME}. Skipping...")
    endif()
endif()

