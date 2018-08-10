# © 2018 Joseph Cameron - All Rights Reserved
# Created on 2018-04-13.

set(dependencies
    "glm"
    "stb"
    #"tinyobjloader"
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    list(APPEND dependencies
        "emscripten"
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    list(APPEND dependencies
        "glfw"    
    )
endif()

jfc_add_submodule_dependencies(${dependencies})
