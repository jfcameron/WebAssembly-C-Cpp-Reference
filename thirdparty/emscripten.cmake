# © 2018 Joseph Cameron - All Rights Reserved
# Created on 2018-05-11.

set(${JFC_DEPENDENCY_NAME}_INCLUDE_DIR 
    "${CMAKE_CURRENT_LIST_DIR}/${JFC_DEPENDENCY_NAME}/system/include"
    CACHE PATH "${JFC_DEPENDENCY_NAME} include directory" FORCE)

set(${JFC_DEPENDENCY_NAME}_LIBRARIES     
    CACHE PATH "${JFC_DEPENDENCY_NAME} library object list" FORCE)
