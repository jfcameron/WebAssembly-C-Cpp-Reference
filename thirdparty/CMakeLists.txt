# © 2018 Joseph Cameron - All Rights Reserved

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

jfc_add_dependencies(
    GIT_SUBMODULES
        ${submodule_dependencies}
)
