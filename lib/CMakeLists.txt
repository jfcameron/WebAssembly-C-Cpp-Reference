# © 2018 Joseph Cameron - All Rights Reserved
# Created on 2018-05-14.

include("${CMAKE_SOURCE_DIR}/cmake/jfclib.cmake")

if (JFC_BUILD_LIB)
    project("gdk"
        VERSION "1.0" 
        DESCRIPTION "WebAssembly project shareable code")

    add_library(${PROJECT_NAME} STATIC
	${CMAKE_CURRENT_SOURCE_DIR}/src/camera.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/color.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/defaultresources.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/exception.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/floatuniformcollection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/gdk.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/glfw_wrapper.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/glh.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/graphics_gl.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/intvector2.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/lazy_ptr.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/logger.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/mat4x4.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/mat4x4uniformcollection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/model.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/opengl.cpp        
	${CMAKE_CURRENT_SOURCE_DIR}/src/quaternion.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/shaderprogram.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/texture.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/textureuniformcollection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/time.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/trigonometry.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vector2.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vector2uniformcollection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vector3.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vector3uniformcollection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vector4.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vector4uniformcollection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vertexattribute.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vertexdata.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/vertexformat.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/webapis_wrapper.cpp        
    )
    
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${stb_INCLUDE_DIR}
        ${glm_INCLUDE_DIR}        
        ${emscripten_INCLUDE_DIR})

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
	    set(COMMON_CXX_FLAGS "-std=c++17 -pthread -Wall -Werror \
	    -Wno-c++11-narrowing -Wno-unused-local-typedef -Wno-unused-const-variable -Wno-unused-function")#These should be removed for more strict error checking
        set(WASM_CXX_FLAGS "-s BINARYEN=1 -s \"BINARYEN_METHOD='native-wasm'\" -s DEMANGLE_SUPPORT=1")

        if(UNIX)
            set(CMAKE_CXX_FLAGS         "$ENV{CXXFLAGS} ${COMMON_CXX_FLAGS} ${WASM_CXX_FLAGS}")
            set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} ${COMMON_CXX_FLAGS} ${WASM_CXX_FLAGS}")
            set(CMAKE_CXX_FLAGS_DEBUG   "$ENV{CXXFLAGS} ${COMMON_CXX_FLAGS} ${WASM_CXX_FLAGS}")
        endif()

        set(${PROJECT_NAME}_COMPILER_PARAMETERS
            "-s USE_GLFW=3 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1"
            CACHE PATH "${PROJECT_NAME}_COMPILER_PARAMETERS list of required emcc params for ${PROJECT_NAME}" FORCE)
    endif()
endif()
