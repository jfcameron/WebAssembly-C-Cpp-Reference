# © 2018 Joseph Cameron - All Rights Reserved

#================================================================================================
# Debug
#================================================================================================
# print a message with colorized text of form: [TAGNAME] MESSAGEBODY
#    @param aLogLevel: standard cmake log levels e.g: STATUS, FATAL_ERROR
#    @param aTag: Hint about where in the project the log is coming from
#    @param aMessage: content of message 
function(jfc_log aLogLevel aTag aMessage)
    if (NOT WIN32)
        string(ASCII 27 JFC_ESC) # "\"

        set(JFC_STYLE_NONE  "${JFC_ESC}[m")
        set(JFC_STYLE_TAG   "${JFC_ESC}[38;5;3m")
        set(JFC_STYLE_ERROR "${JFC_ESC}[31m")
        set(JFC_STYLE_WARN  "${JFC_ESC}[35m")
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

# log all variables in the global scope and halt execution.
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

#================================================================================================
# Thirdparty
#================================================================================================
# build a dependant library project
#    @param aName: name of repository
#    Assumptions: 
#        - this is a git project
#        - a submodule to the repo {aName} has been added to this project and exists in {CMAKE_CURRENT_SOURCE_DIR}
#        - a file named {aName}.cmake exists in {CMAKE_CURRENT_SOURCE_DIR}. It should contain instructions to build the submodule.
#
#    Note: inside of {aName}.cmake the variable {JFC_DEPENDENCY_NAME} is defined with the value of {aName}
#    
#    Example usage:
#        {root}/extern/CMakeLists.txt
#            include("${CMAKE_SOURCE_DIR}/cmake/jfclib.cmake")
#            jfc_add_dependency("MyCoolLib")
#
#        {root}/extern/MyCoolLib.cmake
#            set(MYCOOLLIB_BUILD_TESTS OFF CACHE BOOL "Disabled testing for ${JFC_DEPENDENCY_NAME}")
#            set(MYCOOLLIB_INSTALL OFF)
#
#            add_subdirectory(${JFC_DEPENDENCY_NAME})
#
#            set(${JFC_DEPENDENCY_NAME}_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/${JFC_DEPENDENCY_NAME}/include"
#                CACHE PATH "${JFC_DEPENDENCY_NAME} include directory" FORCE)
#
#            set(${JFC_DEPENDENCY_NAME}_LIBRARIES "${CMAKE_BINARY_DIR}/extern/MyCoolLib/src/libMyCoolLib.a"
#                CACHE PATH "${JFC_DEPENDENCY_NAME} library object list" FORCE) 
function(jfc_add_dependencies)
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

    MATH(EXPR ARGC "${ARGC}-1")

    foreach(loop_var RANGE ${ARGC})
        jfc_add_dependency("${ARGV${loop_var}}")
    endforeach()
endfunction()

#================================================================================================
# Root
#================================================================================================
# Recalculates the path to the root of the current git repo, writing to JFC_CURRENT_REPO_ROOT
#[[function(jfc_get_git_repo_root)
    execute_process(COMMAND git rev-parse --show-toplevel
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE _RESULT
        OUTPUT_VARIABLE _OUTPUT)

    set(JFC_CURRENT_REPO_ROOT ${_OUTPUT} PARENT_SCOPE)
    
    if (NOT ${_LAST_PROCESS_RESULT} MATCHES "0")
        message(FATAL_ERROR "${_LAST_PROCESS_RESULT}")
    endif()
endfunction()

jfc_get_git_repo_root()]]

#====================
# Private utilities
#====================
# loops...

#================================================================================================
# Projects
#================================================================================================
function(jfc_project)
    set(_Required_Simple_Fields
        "NAME"
        "VERSION"
        "DESCRIPTION"
        "C++_STANDARD"
        "C_STANDARD")

    set(_Required_List_Fields
        "SOURCE_LIST"
        "INCLUDE_DIRECTORIES"
        "LIBRARIES")

    set(_parse_mode "PARSE_SIMPLE_FIELDS") # PARSE_SIMPLE_FIELDS | any member of _Required_List_Fields

    macro(_pop_front)
        list(REMOVE_AT ARGV 0)
        list(LENGTH ARGV _s)
    endmacro()

    set(TAG "PROJECT")

    list(LENGTH ARGV _s)
    while(_s GREATER 0)
        list(LENGTH ARGV _s)
        list(GET ARGV 0 _item)

        if (_parse_mode STREQUAL "PARSE_SIMPLE_FIELDS")
            list(FIND _Required_Simple_Fields ${_item} _item_is_a_required_field) # do simple
            if (_item_is_a_required_field GREATER_EQUAL 0)
                if (${_s} GREATER 1)
                    list(GET ARGV 1 _value)

                    list(FIND _Required_Simple_Fields ${_value} _value_is_a_required_field)

                    if (_value_is_a_required_field GREATER_EQUAL 0)
                        jfc_log(FATAL_ERROR ${TAG} "value of ${_item} is a requiredfield \"${_value}\"")
                    endif()
                
                    set("${_item}_value" ${_value})

                    _pop_front()
                else()
                    jfc_log(FATAL_ERROR ${TAG} "${ARGV${_found_index}} requires a value")
                endif()
            else()
                list(FIND _Required_List_Fields ${_item} _item_is_a_required_list_field) # flip mode
                if (_item_is_a_required_list_field GREATER_EQUAL 0)
                    set(_parse_mode ${_item})
                else()
                    jfc_log(FATAL_ERROR ${TAG} "\"${_item}\" is a value without a field!")
                endif()
            endif()

            _pop_front()
        else() # Parsing a list
            list(FIND _Required_Simple_Fields ${_item} _item_is_a_required_field)
            list(FIND _Required_List_Fields ${_item} _item_is_a_required_list_field)
            if (_item_is_a_required_field GREATER_EQUAL 0 OR _item_is_a_required_list_field GREATER_EQUAL 0)
                set(_parse_mode "PARSE_SIMPLE_FIELDS")
            else()
                set(VALUES_POSTFIX "_values" PARENT_SCOPE) #Need a var to expand

                list(APPEND "${_parse_mode${VALUES_POSTFIX}}" "${_item}")

                _pop_front()
            endif()
        endif()
    endwhile()

    # ======================== Using the stuff ===========================
   
    #[[foreach(field ${_Required_Simple_Fields})
        jfc_log(STATUS ${TAG} "${field}: ${${field}_value}")
    endforeach()]]

    foreach(list ${_Required_List_Fields})
        set (list_values ${list${VALUES_POSTFIX}})
        list(LENGTH ${list_values} _s)

        jfc_log(STATUS ${TAG} "${list}:")

        set(_i "0")
        while(${_i} LESS ${_s})
            list(GET "${list_values}" ${_i} value)
            
            jfc_log(STATUS ${TAG} "\t${value}")

            if (NOT ${list}_value)
                set(${list}_value "${value}")
            else()
                string(CONCAT ${list}_value "${${list}_value}\n\t\t" "${value}")
            endif()
            
            MATH(EXPR _i "${_i}+1")
        endwhile()
    endforeach()

    JFC_LOG(STATUS "BLAR" "${NAME_value}")

    #generate project
    set(THE_MESSAGE "blarblarblarHellogenerated!")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/project.cmake.in
        "${CMAKE_BINARY_DIR}/${NAME_value}.cmake" @ONLY)

    include("${CMAKE_BINARY_DIR}/${NAME_value}.cmake")
endfunction()