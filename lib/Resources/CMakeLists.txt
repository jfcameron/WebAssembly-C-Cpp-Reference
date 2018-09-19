# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

#[[if(NOT CMAKE_SYSTEM_NAME MATCHES "Emscripten") # very much a hack
    set(PLATFORM_SPECIFIC_SOURCE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src/httprequest.cpp
    )
endif()]]

jfc_project(library
    NAME "gdkresources"
    VERSION 0.0
    DESCRIPTION "game development kit local & remote resource loader lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        ${nlohmann_INCLUDE_DIR}

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

        ${gdkdebug_INCLUDE_DIRECTORIES}
        ${gdkmemory_INCLUDE_DIRECTORIES}
        
        ${curl_INCLUDE_DIR}
        ${sqlite_INCLUDE_DIR}

    LIBRARIES
        ${gdkdebug_LIBRARIES}
        
        ${curl_LIBRARIES}
        ${sqlite_LIBRARIES}

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/database.cpp
        ${PLATFORM_SPECIFIC_SOURCE} #????
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