# © 2018 Joseph Cameron - All Rights Reserved

project("${JFC_DEPENDENCY_NAME}")

# generates source file and copies headers for the specific stb projects named in ARGV
# eg: import_stb_projects("stb_image" "stb_perlin") will make available stb_image, perlin headers and define their symbols.
function(import_stb_projects)
    # Generate implementation for stb
    foreach(_arg ${ARGV})
        string(TOUPPER ${_arg} _arg_upper)

        string(APPEND _stb_imp_file_contents "#define ${_arg_upper}_IMPLEMENTATION\n#include \"stb/${_arg}.h\"\n")
    endforeach()

    file(WRITE "${PROJECT_BINARY_DIR}/stb_implementation.c" "${_stb_imp_file_contents}")

    # Move selected headers to workspace
    foreach(_arg ${ARGV})
        file(COPY "${CMAKE_CURRENT_LIST_DIR}/stb/${_arg}.h" 
            DESTINATION "${PROJECT_BINARY_DIR}/include/stb/")
    endforeach()
endfunction()

import_stb_projects(
    "stb_image"
)

# build lib
add_library(${PROJECT_NAME} STATIC
    ${PROJECT_BINARY_DIR}/stb_implementation.c)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_BINARY_DIR}/include/)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)

# Define dependency symbols
set(${PROJECT_NAME}_INCLUDE_DIR
    ${PROJECT_BINARY_DIR}/include
    CACHE PATH "${PROJECT_NAME}_INCLUDE_DIR include directory" FORCE)

set(${PROJECT_NAME}_LIBRARIES
    ${PROJECT_BINARY_DIR}/lib${PROJECT_NAME}.a
    CACHE PATH "${PROJECT_NAME}_LIBRARIES library object list" FORCE)
