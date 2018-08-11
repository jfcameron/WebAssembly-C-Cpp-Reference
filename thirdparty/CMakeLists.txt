# © 2018 Joseph Cameron - All Rights Reserved
# Created on 2018-04-13.

set(submodule_dependencies
    "glm"
    "stb"
)

if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    list(APPEND submodule_dependencies
        "emscripten"
    )
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    list(APPEND submodule_dependencies
        "glfw"    
    )
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    list(APPEND submodule_dependencies
        "glfw"
    )
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    list(APPEND submodule_dependencies
        "glfw"
    )
endif()

jfc_add_submodule_dependencies(${submodule_dependencies})

#... how to deal with release dependencies?
