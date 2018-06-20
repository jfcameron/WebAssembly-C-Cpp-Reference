# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

include("${CMAKE_SOURCE_DIR}/cmake/jfclib.cmake")

if (JFC_BUILD_LIB)
    project("gdk"
        VERSION "0.0" 
        DESCRIPTION "WebAssembly project shareable code")

    add_library(${PROJECT_NAME} STATIC
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
    
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${stb_INCLUDE_DIR}
        ${glm_INCLUDE_DIR}) 

    set_target_properties(${PROJECT_NAME} PROPERTIES RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

    #set_property(TARGET ${PROJECT_NAME} PROPERTY   C_STANDARD 11)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
    
    set(${PROJECT_NAME}_INCLUDE_DIR
        ${CMAKE_CURRENT_LIST_DIR}/include
        CACHE PATH "${PROJECT_NAME}_INCLUDE_DIR include directory" FORCE)
    
    set(${PROJECT_NAME}_LIBRARIES
        ${PROJECT_BINARY_DIR}/lib${PROJECT_NAME}.a;
        ${stb_LIBRARIES}
        CACHE PATH "${PROJECT_NAME}_LIBRARIES library object list" FORCE)

    if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	target_include_directories(${PROJECT_NAME} PRIVATE
		${emscripten_INCLUDE_DIR})
        
	set(${PROJECT_NAME}_COMPILER_PARAMETERS
            #"-s WASM=1 -s USE_GLFW=3 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1 -s ASYNCIFY=1 -s DEMANGLE_SUPPORT=1" #-s ASYNCIFY=1
            "-s WASM=1 -s USE_GLFW=3 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1 -s DEMANGLE_SUPPORT=1 -s FETCH=1 --preload-file resource/test.txt --preload-file resource/awesome.png"
            CACHE PATH "${PROJECT_NAME}_COMPILER_PARAMETERS list of required emcc params for ${PROJECT_NAME}" FORCE)
    endif()
endif()
