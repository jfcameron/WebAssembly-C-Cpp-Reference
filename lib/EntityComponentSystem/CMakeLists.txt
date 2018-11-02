# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

#if (JFC_BUILD_LIB)
    project("gdkentitycomponentsystem"
        VERSION "0.0"
        DESCRIPTION "GDK Entity Component System core library")

    add_library(${PROJECT_NAME} STATIC
        # Core
    	${CMAKE_CURRENT_SOURCE_DIR}/src/component.cpp
    	${CMAKE_CURRENT_SOURCE_DIR}/src/gameobject.cpp
    	${CMAKE_CURRENT_SOURCE_DIR}/src/scene.cpp
    	${CMAKE_CURRENT_SOURCE_DIR}/src/scenegraph.cpp
    	${CMAKE_CURRENT_SOURCE_DIR}/src/scenemanager.cpp

        #hacks
        #${CMAKE_CURRENT_SOURCE_DIR}/src/hack.cpp
    )
    
    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${stb_INCLUDE_DIR}
        ${glm_INCLUDE_DIR})

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
#endif()
