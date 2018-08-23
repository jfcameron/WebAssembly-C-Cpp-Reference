# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/jfc-cmake/jfclib.cmake")

option(JFC_BUILD_APP    "Build the app" ON)
option(JFC_BUILD_DOCS   "Build documentation" OFF)
option(JFC_BUILD_TESTS  "Build unit tests" OFF)
#option(JFC_AUTO_RUN_APP "Auto run the app on build" OFF) #todo: implement
#option(JFC_FORMAT_CODE  "Format code with a tool" OFF)

set(CMAKE_CXX_FLAGS "-g") # what is this here for

if(JFC_BUILD_DOCS)
    add_subdirectory(docs)
endif()

if(JFC_BUILD_TESTS)
    add_subdirectory(test)
endif()

add_subdirectory(thirdparty)
    #add_subdirectory(resources)
add_subdirectory(lib)

if(JFC_BUILD_APP)
    add_subdirectory(src)
endif()
