# © 2018 Joseph Cameron - All Rights Reserved

set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
set(GLFW_INSTALL OFF CACHE BOOL "")
#set(GLFW_VULKAN_STATIC OFF CACHE BOOL "")

add_subdirectory(${JFC_DEPENDENCY_NAME})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(CORE_VIDEO CoreVideo)
    FIND_LIBRARY(IO_KIT IOKit)    

    #    find_package(vulkan REQUIRED)
    find_package(OpenGL REQUIRED)
else()
    message(FATAL_ERROR "${JFC_DEPENDENCY_NAME}.cmake has not been configured to handle platform \"${JFC_TARGET_PLATFORM}\".")
endif()

set(${JFC_DEPENDENCY_NAME}_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/${JFC_DEPENDENCY_NAME}/include;${OPENGL_INCLUDE_DIR}"#;${Vulkan_INCLUDE_DIR}"
    CACHE PATH "${JFC_DEPENDENCY_NAME} include directory" FORCE)

set(${JFC_DEPENDENCY_NAME}_LIBRARIES 
    ${CMAKE_BINARY_DIR}/thirdparty/glfw/src/libglfw3.a
    ${COCOA_LIBRARY}
    ${CORE_VIDEO} 
    ${IO_KIT} 

    ${OPENGL_LIBRARIES}
#    ${Vulkan_LIBRARIES}

    CACHE PATH "${JFC_DEPENDENCY_NAME} library object list" FORCE)
