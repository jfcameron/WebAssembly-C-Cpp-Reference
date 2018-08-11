# © 2018 Joseph Cameron - All Rights Reserved

jfc_project(executable
    NAME "main"
    VERSION 1.0
    DESCRIPTION "GDK app compiling for web as wasm"
    C++_STANDARD 17
    C_STANDARD 90

    PRIVATE_INCLUDE_DIRECTORIES
        ${gdk_INCLUDE_DIRECTORIES}

    LIBRARIES
        ${gdk_LIBRARIES}
    
    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# Move this stuff to gdk_project.
if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${emscripten_INCLUDE_DIR})

    set(gdk_EMSCRIPTEN_LINK_FLAGS
        "-s WASM=1 -s USE_GLFW=3 -s DISABLE_EXCEPTION_CATCHING=0 -s EXCEPTION_DEBUG=1 -s DEMANGLE_SUPPORT=1 -s FETCH=1 --preload-file resource/test.txt --preload-file resource/awesome.png" # Resources are inapropriate here
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-o ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.js ${gdk_EMSCRIPTEN_LINK_FLAGS}")
    
    jfc_emscripten_generate_index_html_for_current_project()

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    target_link_libraries(${PROJECT_NAME} -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic)
endif()
