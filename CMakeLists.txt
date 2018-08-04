# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/jfclib.cmake")

option(JFC_BUILD_DOCS   "Build documentation" OFF)
option(JFC_BUILD_APP    "Build the app" ON)
option(JFC_BUILD_LIB    "Build the reusable component of the app." ON)
option(JFC_BUILD_TESTS  "Build unit tests" OFF)
option(JFC_AUTO_RUN_APP "Auto run the app on build" OFF)
option(JFC_FORMAT_CODE  "Format code with a tool" OFF)

#add_subdirectory(docs)
add_subdirectory(test)
add_subdirectory(thirdparty)
#add_subdirectory(resources)
add_subdirectory(lib)
add_subdirectory(src)

jfc_generate_readme_md(
    BRIEF "Reference project demonstrating how to compile C or C++ source to webassembly using CMake and Emscripten."
#    DESCRIPTION "."
 #   IMAGES
  #      thing.png
   #     blar.gif
    #    zip.jpg
)
