# © 2018 Joseph Cameron - All Rights Reserved

set(_DESCRIPTION_ROOT "game development kit")

jfc_project(library
    NAME "gdkdebug"
    VERSION 0.0
    DESCRIPTION "${_DESCRIPTION_ROOT}: debug facilities for gdk"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/exception.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/logger.cpp
)

jfc_project(library
    NAME "gdkmath"
    VERSION 0.0
    DESCRIPTION "${_DESCRIPTION_ROOT}: math lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        
    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${glm_INCLUDE_DIR}

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/intvector2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mat4x4.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/quaternion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/trigonometry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/vector4.cpp
)

jfc_project(library
    NAME "gdkgraphics"
    VERSION 0.0
    DESCRIPTION "${_DESCRIPTION_ROOT}: graphics lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${gdkmath_INCLUDE_DIRECTORIES}
        ${stb_INCLUDE_DIR}

    LIBRARIES
        ${gdkmath_LIBRARIES}
        ${stb_LIBRARIES}

    SOURCE_LIST
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
)

jfc_project(library
    NAME "gdkinput"
    VERSION 0.0
    DESCRIPTION "${_DESCRIPTION_ROOT}: HID lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

        ${glfw_INCLUDE_DIR} #hmm
    
    #LIBRARIES

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/keyboard.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mouse.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gamepads.cpp
)

jfc_project(library
    NAME "gdkresources"
    VERSION 0.0
    DESCRIPTION "${_DESCRIPTION_ROOT}: local & remote resource loader lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${stb_INCLUDE_DIR}

    #LIBRARIES

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.cpp
)

jfc_project(library
    NAME "gdk"
    VERSION 0.0
    DESCRIPTION "${_DESCRIPTION_ROOT}"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include # should be private

    PRIVATE_INCLUDE_DIRECTORIES
        ${gdkdebug_INCLUDE_DIRECTORIES}
        ${gdkgraphics_INCLUDE_DIRECTORIES}
        ${gdkinput_INCLUDE_DIRECTORIES}
        ${gdkmath_INCLUDE_DIRECTORIES}
        ${gdkresources_INCLUDE_DIRECTORIES}
        ${stb_INCLUDE_DIR}
        ${glm_INCLUDE_DIR}

        ${glfw_INCLUDE_DIR}

    LIBRARIES
        ${gdkdebug_LIBRARIES}
        ${gdkgraphics_LIBRARIES}
        ${gdkinput_LIBRARIES}
        ${gdkmath_LIBRARIES}
        ${gdkresources_LIBRARIES}
        ${stb_LIBRARIES}

        ${glfw_LIBRARIES}

    SOURCE_LIST
        # Core
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gdk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glfw_wrapper.cpp # Not sure where to put this. It is implementation detail of multiple libs for desktop & emscripten platforms
        
        # Time
        ${CMAKE_CURRENT_SOURCE_DIR}/src/time.cpp

        #hacks
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hack.cpp
)

# This works but should be moved. Here the platform specific work only applies to the GDK root project. It should be applied to each separate lib that actually needs it.
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${emscripten_INCLUDE_DIR})

    set(${PROJECT_NAME}_EMSCRIPTEN_LINK_FLAGS
        "-s WASM=1 -s USE_GLFW=3 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1 -s DEMANGLE_SUPPORT=1 -s FETCH=1 --preload-file resource/test.txt --preload-file resource/awesome.png" # Resources are inapropriate here
        CACHE PATH "${PROJECT_NAME}_EMSCRIPTEN_LINK_FLAGS list of required emcc params for ${PROJECT_NAME}" FORCE
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#[[    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(CORE_VIDEO CoreVideo)
    FIND_LIBRARY(IO_KIT IOKit)
    FIND_LIBRARY(OPENGL OpenGL)

    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${COCOA_LIBRARY} 
        ${CORE_VIDEO} 
        ${IO_KIT} 
        ${OPENGL}
    )]]
endif()
