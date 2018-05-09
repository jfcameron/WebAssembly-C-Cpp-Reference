# © 2018 Joseph Cameron - All Rights Reserved

#[[message(AUTHOR_WARNING "\
special variables from within jfclib.cmake:\n\
CMAKE_CURRENT_LIST_FILE: ${CMAKE_CURRENT_LIST_FILE}\n\
CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}\n\
")]]

#[[! print a message with colorized text
    @param aLogLevel: standard cmake log levels e.g: STATUS, FATAL_ERROR
    @param aTag: Hint about where in the project the log is coming from
    @param aMessage: content of message ]]
function(jfc_log aLogLevel aTag aMessage)
    if(NOT WIN32)
        string(ASCII 27 JFC_ESC)
        set(JFC_STYLE_NONE "${JFC_ESC}[m")
        set(JFC_STYLE_TAG "${JFC_ESC}[38;5;3m")
        set(JFC_STYLE_ERROR "${JFC_ESC}[31m")
        set(JFC_STYLE_WARN "${JFC_ESC}[35m")
    endif()
    
    set(message_buffer "${JFC_STYLE_TAG}[${aTag}]${JFC_STYLE_NONE} ")
    
    if ("${aLogLevel}" STREQUAL "FATAL_ERROR" OR "${aLogLevel}" STREQUAL "SEND_ERROR")
        string(CONCAT message_buffer "${message_buffer}" "${JFC_STYLE_ERROR}error:${JFC_STYLE_NONE} ")
    elseif ("${aLogLevel}" STREQUAL "WARNING" OR "${aLogLevel}" STREQUAL "AUTHOR_WARNING" OR "${aLogLevel}" STREQUAL "DEPRECATION")
        string(CONCAT message_buffer "${message_buffer}" "${JFC_STYLE_WARN}warn:${JFC_STYLE_NONE} ")
    endif()

    string(CONCAT message_buffer "${message_buffer}" "${aMessage}")

    message("${aLogLevel}" "${message_buffer}")
endfunction()

#[[! build a dependant library project
    @param aName: name of repository
    Assumptions: 
        - this is a git project
        - a submodule to the repo {aName} has been added to this project and exists in {CMAKE_CURRENT_SOURCE_DIR}
        - a file named {aName}.cmake exists in {CMAKE_CURRENT_SOURCE_DIR}. It should contain instructions to build the submodule.

    Note: inside of {aName}.cmake the variable {JFC_DEPENDENCY_NAME} is defined with the value of {aName}
    
    Example usage:
        {root}/extern/CMakeLists.txt
            include("${CMAKE_SOURCE_DIR}/cmake/jfclib.cmake")
            jfc_add_dependency("MyCoolLib")

        {root}/extern/MyCoolLib.cmake
            set(MYCOOLLIB_BUILD_TESTS OFF CACHE BOOL "Disabled testing for ${JFC_DEPENDENCY_NAME}")
            set(MYCOOLLIB_INSTALL OFF)

            add_subdirectory(${JFC_DEPENDENCY_NAME})

            set(${JFC_DEPENDENCY_NAME}_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/${JFC_DEPENDENCY_NAME}/include"
                CACHE PATH "${JFC_DEPENDENCY_NAME} include directory" FORCE)

            set(${JFC_DEPENDENCY_NAME}_LIBRARIES "${CMAKE_BINARY_DIR}/extern/MyCoolLib/src/libMyCoolLib.a"
                CACHE PATH "${JFC_DEPENDENCY_NAME} library object list" FORCE) ]]
function(jfc_add_dependency aName)
    set(TAG "Library loading stage")

    jfc_log(STATUS ${TAG} "Processing submodule dependency \"${aName}\".")

    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${aName}.cmake)
        jfc_log(FATAL_ERROR ${TAG} "${CMAKE_CURRENT_SOURCE_DIR}/${aName}.cmake does not exist. This is required to instruct the loader how to build dependency \"${aName}\".")
    endif()

    execute_process(COMMAND git submodule update --init -- ${CMAKE_CURRENT_SOURCE_DIR}/${aName}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_RETURN_VALUE
        OUTPUT_VARIABLE GIT_ERRORS)

    if (GIT_RETURN_VALUE)
        jfc_log(FATAL_ERROR ${TAG} "git submodule \"${aName}\" init failed. Does it exist? Raw error message: ${JFC_GIT_ERROR}")
    endif()

    set(JFC_DEPENDENCY_NAME "${aName}")

    include("${aName}.cmake")

    if (NOT DEFINED ${aName}_LIBRARIES)
        jfc_log(WARNING ${TAG} "${aName}.cmake did not define a variable \"${aName}_LIBRARIES\". Is it header only?")
    endif()

    if (NOT DEFINED ${aName}_INCLUDE_DIR)
        jfc_log(FATAL_ERROR ${TAG} "${aName}.cmake did not define a variable \"${aName}_INCLUDE_DIR\".")
    endif()

    jfc_log(STATUS ${TAG} "Done processing submodule dependency \"${aName}\". ${aName}_INCLUDE_DIR: ${${aName}_INCLUDE_DIR}, ${aName}_LIBRARIES: ${${aName}_LIBRARIES}")
endfunction()

#[[! log all variables in the global scope and halt execution. ]]
function(jfc_print_all_variables_and_halt)
    get_cmake_property(cmakevars VARIABLES)
    
    list(SORT cmakevars)
    set(output "")
    
    foreach (currentvar ${cmakevars})
        string(CONCAT output "${output}" "${currentvar}=${${currentvar}}\n")
    endforeach()

    jfc_log(STATUS "Dump" "Called from ${CMAKE_CURRENT_LIST_FILE}...\n${output}")
    message(FATAL_ERROR "Dump end.")
endfunction()
