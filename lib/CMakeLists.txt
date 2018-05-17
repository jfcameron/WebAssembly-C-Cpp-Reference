# © 2018 Joseph Cameron - All Rights Reserved
# Created on 2018-05-14.

include("${CMAKE_SOURCE_DIR}/cmake/jfclib.cmake")

if (JFC_BUILD_LIB)
    project("lib"
        VERSION "1.0" 
        DESCRIPTION "WebAssembly project shareable code")

    add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gdk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glfw_wrapper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/graphics_gl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mesh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaderprogram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vertexattribute.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vertexformat.cpp
    )
    
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${stb_INCLUDE_DIR}
        ${emscripten_INCLUDE_DIR})

    set_target_properties(${PROJECT_NAME} PROPERTIES
        RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

    #[[set_property(TARGET ${PROJECT_NAME} PROPERTY
	C_STANDARD 11)]]
      
    target_compile_features(${PROJECT_NAME}
        ${JFC_CXX_COMPILER_FEATURE_REQUIREMENTS})
    
    #add symbols
    set(${PROJECT_NAME}_INCLUDE_DIR
        ${CMAKE_CURRENT_LIST_DIR}/include
        CACHE PATH "${PROJECT_NAME}_INCLUDE_DIR include directory" FORCE)
    
    set(${PROJECT_NAME}_LIBRARIES
        ${PROJECT_BINARY_DIR}/lib${PROJECT_NAME}.a;
        ${stb_LIBRARIES}
        CACHE PATH "${PROJECT_NAME}_LIBRARIES library object list" FORCE)
endif()
