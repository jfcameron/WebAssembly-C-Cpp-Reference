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
        ${glfw_INCLUDE_DIR} # this was required on windwos to get access to glew. This is a good reason to separate the two

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

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gamepads.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/keyboard.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/mouse.cpp
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

        ${nlohmann_INCLUDE_DIR}

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        
        ${stb_INCLUDE_DIR}
        ${glfw_INCLUDE_DIR} # this was required on windwos to get access to glew. This is a good reason to separate the two
        ${curl_INCLUDE_DIR}

    LIBRARIES
        ${curl_LIBRARIES}

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/httprequest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/resources.cpp
)

jfc_project(library
    NAME "gdktime"
    VERSION 0.0
    DESCRIPTION "${_DESCRIPTION_ROOT} time lib"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

    PRIVATE_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/time.cpp

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
        ${gdktime_INCLUDE_DIRECTORIES}

        ${glfw_INCLUDE_DIR}
        ${glm_INCLUDE_DIR}
        ${stb_INCLUDE_DIR}

    LIBRARIES
        ${gdkdebug_LIBRARIES}
        ${gdkgraphics_LIBRARIES}
        ${gdkinput_LIBRARIES}
        ${gdkmath_LIBRARIES}
        ${gdkresources_LIBRARIES}
        ${gdktime_LIBRARIES}
        
        ${glfw_LIBRARIES}
        ${stb_LIBRARIES}

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/src/gdk.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/glfw_wrapper.cpp # Not sure where to put this. It is implementation detail of multiple libs for desktop & emscripten platforms
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hack.cpp
)
