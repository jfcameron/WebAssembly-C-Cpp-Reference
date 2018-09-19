# © 2018 Joseph Cameron - All Rights Reserved

# builds the contained source code release of sqlite. sqlite uses a unique version control system "fossil" so cannot do anything fancy with git.

file(COPY "${CMAKE_CURRENT_LIST_DIR}/${JFC_DEPENDENCY_NAME}/sqlite3.h" 
    DESTINATION "${PROJECT_BINARY_DIR}/include/${JFC_DEPENDENCY_NAME}/")

file(COPY "${CMAKE_CURRENT_LIST_DIR}/${JFC_DEPENDENCY_NAME}/sqlite3ext.h" 
    DESTINATION "${PROJECT_BINARY_DIR}/include/${JFC_DEPENDENCY_NAME}/")

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_LIST_DIR}/${JFC_DEPENDENCY_NAME}/shell.c
    ${CMAKE_CURRENT_LIST_DIR}/${JFC_DEPENDENCY_NAME}/sqlite3.c)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_BINARY_DIR}/include/)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "${PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>")

jfc_set_dependency_symbols(
    INCLUDE_PATHS
        ${PROJECT_BINARY_DIR}/include

    LIBRARIES
        ${PROJECT_BINARY_DIR}/lib${JFC_DEPENDENCY_NAME}.a
)
