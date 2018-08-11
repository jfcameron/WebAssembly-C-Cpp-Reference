# © 2018 Joseph Cameron - All Rights Reserved

jfc_log(STATUS "blarblar" "glfw has started processing")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")
#set(GLFW_VULKAN_STATIC OFF CACHE BOOL "")

add_subdirectory(${JFC_DEPENDENCY_NAME})

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(CORE_VIDEO CoreVideo)
    FIND_LIBRARY(IO_KIT IOKit)    

    find_package(OpenGL REQUIRED) # find_package(vulkan REQUIRED)

elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
    find_package(OpenGL REQUIRED)
    find_package(X11 REQUIRED)
    find_package(Threads REQUIRED)

    # Trying to hide glew in glfw makes some sense but its kind of hard to read
    project("GLEW")

    add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/src/glew.c)

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/include)

    set_target_properties(${PROJECT_NAME} PROPERTIES
        RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

    set(GLEW_LIBRARIES ${CMAKE_BINARY_DIR}/thirdparty/libGLEW.a)
    set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/include)

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    find_package(OpenGL REQUIRED)

    # Trying to hide glew in glfw makes some sense but its kind of hard to read
    project("GLEW")

    add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/src/glew.c)

    target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/include)

    set_target_properties(${PROJECT_NAME} PROPERTIES
        RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

    set(GLEW_LIBRARIES ${CMAKE_BINARY_DIR}/thirdparty/libGLEW.a)
    set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/glew-2.1.0/include)

else()
    message(FATAL_ERROR "${JFC_DEPENDENCY_NAME}.cmake has not been configured to handle platform \"${CMAKE_SYSTEM_NAME}\".")
endif()

set(${JFC_DEPENDENCY_NAME}_INCLUDE_DIR 
    ${CMAKE_CURRENT_LIST_DIR}/${JFC_DEPENDENCY_NAME}/include
    
    ${OPENGL_INCLUDE_DIR} #${Vulkan_INCLUDE_DIR} # vulk?

    # Linux
    ${GLEW_INCLUDE_DIR}
    ${X11_INCLUDE_DIR}

    CACHE PATH "${JFC_DEPENDENCY_NAME} include directory" FORCE)

set(${JFC_DEPENDENCY_NAME}_LIBRARIES 
    ${CMAKE_BINARY_DIR}/thirdparty/glfw/src/libglfw3.a

    #Macos specifc
    ${COCOA_LIBRARY}
    ${CORE_VIDEO} 
    ${IO_KIT} 

    ${OPENGL_LIBRARIES} #${Vulkan_LIBRARIES} # Should have option for vulk?

    #Linux specific
    ${GLEW_LIBRARIES}
    ${X11_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
    ${CMAKE_DL_LIBS}

    CACHE PATH "${JFC_DEPENDENCY_NAME} library object list" FORCE)
