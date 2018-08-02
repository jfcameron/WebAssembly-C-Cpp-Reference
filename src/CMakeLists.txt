# © 2018 Joseph Cameron - All Rights Reserved

jfc_project(executable
    NAME "main"
    VERSION 1.0
    DESCRIPTION "GDK app compiling for web as wasm"
    C++_STANDARD 17
    C_STANDARD 90
    #EXECUTABLE_PARAMETERS "macos"

    PRIVATE_INCLUDE_DIRECTORIES
        ${gdk_INCLUDE_DIRECTORIES}

    LIBRARIES
        ${gdk_LIBRARIES}
    
    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
        "-o ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.js ${gdk_EMSCRIPTEN_LINK_FLAGS}")
endif()
