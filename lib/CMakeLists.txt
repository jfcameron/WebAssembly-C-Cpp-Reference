# © 2018 Joseph Cameron - All Rights Reserved

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Debug")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Memory")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Math")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/GLFWWrapper")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Time")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Graphics")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Resources")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Input")

jfc_project(library
    NAME "gdk"
    VERSION 0.0
    DESCRIPTION "game development kit"
    C++_STANDARD 17
    C_STANDARD 90
    TYPE STATIC

    PUBLIC_INCLUDE_DIRECTORIES
        ${CMAKE_CURRENT_SOURCE_DIR}/include

        ${gdkgraphics_INCLUDE_DIRECTORIES}
        ${gdkdebug_INCLUDE_DIRECTORIES}
        #${gdkentitycomponentsystem_INCLUDE_DIRECTORIES}
        ${gdkglfwwrapper_INCLUDE_DIRECTORIES}
        ${gdkinput_INCLUDE_DIRECTORIES}
        ${gdkmath_INCLUDE_DIRECTORIES}
        ${gdkmemory_INCLUDE_DIRECTORIES}
        ${gdkresources_INCLUDE_DIRECTORIES}
        ${gdktime_INCLUDE_DIRECTORIES}

    LIBRARIES
        ${gdkdebug_LIBRARIES}
        #${gdkentitycomponentsystem_LIBRARIES}
        ${gdkglfwwrapper_LIBRARIES}
        ${gdkgraphics_LIBRARIES}
        ${gdkinput_LIBRARIES}
        ${gdkmath_LIBRARIES}
        ${gdkmemory_INCLUDE_DIRECTORIES}
        ${gdkresources_LIBRARIES}
        ${gdktime_LIBRARIES}
        
        ${glfw_LIBRARIES}
        ${stb_LIBRARIES}

    SOURCE_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/delete_me.cpp
)
