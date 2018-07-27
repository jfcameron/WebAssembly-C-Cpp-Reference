# © 2018 Joseph Cameron - All Rights Reserved

jfc_project(library
    NAME "gdk"
    VERSION 0.0
    DESCRIPTION "jfc game development kit"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include # should be private

    PRIVATE_INCLUDE_DIRECTORIES
        ${stb_INCLUDE_DIR}
        ${glm_INCLUDE_DIR}

    LIBRARIES
        ${stb_LIBRARIES}

    SOURCE_LIST
        # Core
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gdk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glfw_wrapper.cpp

        # Debug
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/logger.cpp
     
        # Graphics
        ${CMAKE_CURRENT_SOURCE_DIR}/src/camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/floatuniformcollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glh.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mat4x4uniformcollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/model.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl.cpp        
        ${CMAKE_CURRENT_SOURCE_DIR}/src/shaderprogram.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/texture.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/textureuniformcollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector2uniformcollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector3uniformcollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector4uniformcollection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vertexattribute.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vertexdata.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vertexformat.cpp

        # Input
        ${CMAKE_CURRENT_SOURCE_DIR}/src/keyboard.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mouse.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gamepads.cpp
        
        # Math
        ${CMAKE_CURRENT_SOURCE_DIR}/src/intvector2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mat4x4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/trigonometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector4.cpp

        # Memory
        #...

        # Resources
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.cpp
        
        # Time
        ${CMAKE_CURRENT_SOURCE_DIR}/src/time.cpp

        #hacks
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hack.cpp 
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    #[[target_include_directories(${PROJECT_NAME} PRIVATE
        ${emscripten_INCLUDE_DIR})]]
    
    set(${PROJECT_NAME}_EMSCRIPTEN_LINK_FLAGS
        "-s WASM=1 -s USE_GLFW=3 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1 -s DEMANGLE_SUPPORT=1 -s FETCH=1 --preload-file resource/test.txt --preload-file resource/awesome.png"
        CACHE PATH "${PROJECT_NAME}_EMSCRIPTEN_LINK_FLAGS list of required emcc params for ${PROJECT_NAME}" FORCE)
endif()
