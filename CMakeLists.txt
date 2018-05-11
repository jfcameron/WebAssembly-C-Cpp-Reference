# © 2018 Joseph Cameron - All Rights Reserved
# Created on 2018-05-08.
cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

#cmake -DCMAKE_TOOLCHAIN_FILE=/home/brenden/emsdk_portable/emscripten/master/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -G "Unix Makefiles" .
#set(CMAKE_TOOLCHAIN_FILE cmake/Modules/Platform/Emscripten.cmake)

# Build options
option(JFC_BUILD_DOCS "Build documentation" OFF)

option(JFC_BUILD_TESTS "Build unit tests" OFF)
option(JFC_BUILD_APP "Build the app" ON)
option(JFC_AUTO_RUN_APP "Auto run the app on build" OFF)
option(JFC_FORMAT_CODE "Format code with a tool" OFF)

set(JFC_TARGET_PLATFORM "${CMAKE_HOST_SYSTEM_NAME}" CACHE STRING "Platform to compile the project for")

# Global defines
set(JFC_REPOSITORY_ROOT "${CMAKE_CURRENT_SOURCE_DIR}") #Currently not used

set(JFC_CXX_COMPILER_FEATURE_REQUIREMENTS 
    PRIVATE
        cxx_variadic_templates
        cxx_nullptr
        cxx_lambdas)

####### EMSCRIPTEN HACK STARTS
#this include path has headers for a nubmer of libs including glfw, implemented on web via emscripten project.
set (emscriptenAPIs_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/emscripten/system/include)
    
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
  set(COMMON_CXX_FLAGS "-std=c++11 -Wall -Werror -Wno-c++11-narrowing -Wno-unused-local-typedef -pthread")
  set(WASM_CXX_FLAGS "-s BINARYEN=1 -s \"BINARYEN_METHOD='native-wasm'\" -s DEMANGLE_SUPPORT=1")

  # Set compile flags for emscripten clang
  if(UNIX)
    set(CMAKE_CXX_FLAGS
      "$ENV{CXXFLAGS} ${COMMON_CXX_FLAGS} ${WASM_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE
      "$ENV{CXXFLAGS} ${COMMON_CXX_FLAGS} ${WASM_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG
      "$ENV{CXXFLAGS} ${COMMON_CXX_FLAGS} ${WASM_CXX_FLAGS}")
  endif()
endif()
########
  
#add_subdirectory(docs)
#add_subdirectory(tests)
#add_subdirectory(thirdparty)
#add_subdirectory(shaders)
#add_subdirectory(resources)
add_subdirectory(src)
 
