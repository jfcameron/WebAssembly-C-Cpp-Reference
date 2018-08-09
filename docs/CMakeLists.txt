# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

jfc_generate_documentation_doxygen(
    PROJECT_LOGO ${CMAKE_CURRENT_LIST_DIR}/icon.png

    README_PATH  ../README.md
    
    INCLUDE_DIRECTORIES
        ../lib/include
        ../lib/src/include
)

jfc_generate_readme_md(
    BRIEF "Reference project demonstrating how to compile C or C++ source to webassembly using CMake and Emscripten."
 #   IMAGES
  #      thing.png
   #     blar.gif
    #    zip.jpg
#    DESCRIPTION "."
)
