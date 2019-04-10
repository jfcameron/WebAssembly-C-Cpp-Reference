# © 2018 Joseph Cameron - All Rights Reserved

set(dependencies
    "glm"
    "nlohmann"
    "stb"

    # W I P
    "sqlite"
)

if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    list(APPEND dependencies 
        "emscripten"
    )
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Darwin" OR CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Windows")
    list(APPEND dependencies
        "glfw"
        "curl"
    )
endif()

jfc_add_dependencies(${dependencies})

