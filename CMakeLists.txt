# © 2018 Joseph Cameron - All Rights Reserved

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/jfclib.cmake")

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

# Build options  -> move these to separate modules. (Doc module etc)
option(JFC_BUILD_DOCS "Build documentation" OFF)

option(JFC_BUILD_APP "Build the app" ON)
option(JFC_BUILD_LIB "Build the reusable component of the app." ON)
option(JFC_BUILD_TESTS "Build unit tests" OFF)
option(JFC_AUTO_RUN_APP "Auto run the app on build" OFF)
option(JFC_FORMAT_CODE "Format code with a tool" OFF)

set(JFC_TARGET_PLATFORM "${CMAKE_HOST_SYSTEM_NAME}" CACHE STRING "Platform to compile the project for")

# Global defines
set(JFC_REPOSITORY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}") #Currently not used
  
 #add_subdirectory(docs)
 #add_subdirectory(tests)
#add_subdirectory(thirdparty)
 #add_subdirectory(shaders)
 #add_subdirectory(resources)
#add_subdirectory(lib)
#add_subdirectory(src)
 
jfc_project(
    NAME MyCoolProject
    VERSION 1.0
    DESCRIPTION "This is a project"

    C++_STANDARD 17
    C_STANDARD 11

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gdk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glfw_wrapper.cpp

    HEADER_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${stb_INCLUDE_DIR}
        ${glm_INCLUDE_DIR}

    LIBRARIES
        ${PROJECT_BINARY_DIR}/lib${PROJECT_NAME}.a;
        ${stb_LIBRARIES}
)
