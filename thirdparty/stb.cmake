# © 2018 Joseph Cameron - All Rights Reserved
# Created on 2018-04-15.

# Compile lib
project("${JFC_DEPENDENCY_NAME}")

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/${JFC_DEPENDENCY_NAME}.c)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/${JFC_DEPENDENCY_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)

# Organize headers into standard include format
file(GLOB ${PROJECT_NAME}_HEADER_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/${JFC_DEPENDENCY_NAME}/*.h)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMENT "Creating and populating include/${PROJECT_NAME}" VERBATIM
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${${PROJECT_NAME}_HEADER_FILES} ${PROJECT_BINARY_DIR}/include/${PROJECT_NAME})

# Define dependency symbols
set(${PROJECT_NAME}_INCLUDE_DIR
    ${PROJECT_BINARY_DIR}/include
    CACHE PATH "${PROJECT_NAME}_INCLUDE_DIR include directory" FORCE)

set(${PROJECT_NAME}_LIBRARIES
    ${PROJECT_BINARY_DIR}/lib${PROJECT_NAME}.a
    CACHE PATH "${PROJECT_NAME}_LIBRARIES library object list" FORCE)
