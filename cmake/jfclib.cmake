# © 2018 Joseph Cameron - All Rights Reserved

cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

include_guard(DIRECTORY)

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

# log all variables currently available
# useful for creating diffs to compare between function runs
# useful for identifying and reducing state to avoid sideeffect related bugs
function(jfc_print_all_variables)
    get_cmake_property(cmakevars VARIABLES)
    
    list(SORT cmakevars)
    set(output "")
    
    foreach (currentvar ${cmakevars})
        string(CONCAT output "${output}" "${currentvar}=${${currentvar}}\n")
    endforeach()

    jfc_log(STATUS "Dump" "Called from ${CMAKE_CURRENT_LIST_FILE}...\n${output}")
    jfc_log(STATUS "Dump" "end.")
endfunction()

#================================================================================================
# Utilities
#================================================================================================
# Convert ARGV into a series of options, named variables and named 
# jfc_parse_arguments(${ARGV}
#   OPTIONS
#       blar
#       blam
#   REQUIRED_OPTIONS
#       biff;bop;blap
#   SINGLE_VALUES
#       zip
#   REQUIRED_SINGLE_VALUES
#       zop
#       zap
#   LISTS etcetc
#   REQUIRED_LISTS etc
# )
function(jfc_parse_arguments)
    set(TAG "PARSE")

    # Convert jfc_parse_arguments args into argv_passthrough and a list of criteria
    set(NULL)
    set(_MULTI_VALUE_ARGS
        REQUIRED_OPTIONS REQUIRED_SINGLE_VALUES REQUIRED_LISTS
                 OPTIONS          SINGLE_VALUES          LISTS)

    set(_argv_passthrough)
    foreach(_arg ${ARGV})
        list(FIND _MULTI_VALUE_ARGS ${_arg} _item_is_a_name)

        if (_item_is_a_name GREATER_EQUAL 0)
            break()
        endif()

        list(APPEND _argv_passthrough ${_arg})
    endforeach()
    
    cmake_parse_arguments("_ARG" "${NULL}" "${NULL}" "${_MULTI_VALUE_ARGS}" ${ARGC})

    # At this point prepended argv is available as _argv_passthrough and names
    foreach(name ${_MULTI_VALUE_ARGS})
        jfc_log(STATUS "NAME" "${name}")

        list(LENGTH _ARG_${name} _s)
        set(_i "0")
        while(${_i} LESS ${_s})
            list(GET "_ARG_${name}" ${_i} value)

            jfc_log(STATUS "BLAR" "  ${value}")
            
            MATH(EXPR _i "${_i}+1")
        endwhile()
    endforeach()

    jfc_log(STATUS "ARGV" "${ARGV}")
    
    jfc_log(STATUS "=======================" "")

    # TODO: parse _argv_passthrough with MULTI_VALUE_ARGS 
    set(_OPTIONS_ARGS     "${_ARG_REQUIRED_OPTIONS}"      )# "${_ARG_OPTIONS}")
    set(_ONE_VALUE_ARGS   "${_ARG_REQUIRED_SINGLE_VALUES}")# "${_ARG_SINGLE_VALUES}")
    set(_MULTI_VALUE_ARGS "${_ARG_REQUIRED_LISTS}"      )#   "${_ARG_LISTS}")

    #set(_MULTI_VALUE_ARGS "")
    
    foreach(_item ${_ARG_REQUIRED_LISTS})  # This is not working. TODO!
        list(APPEND _MULTI_VALUE_ARGS ${_item})
    endforeach()

    set(ARGV "${_argv_passthrough}") # is an inner function better than manipulating argv directly?
    list(LENGTH ARGV ARGC)
    
    #may have to do ARGC and argv{n}

    jfc_log(STATUS "ARGV" "ARGV: ${ARGV}") #jfc_log(STATUS "ARGV" "${ARGV}")

    cmake_parse_arguments("_ARG" "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGC})

    list(LENGTH _MULTI_VALUE_ARGS _mvalen)
    list(LENGTH _ARG_MULTI_VALUE_ARGS _mvalenlen)

    jfc_log(STATUS "glorp" "_MULTI_VALUE_ARGS len: ${_mvalen}, _ARG_MULTI_VALUE_ARGS len: ${_mvalenlen}")

    jfc_print_all_variables()

    # Finally, behold
    foreach(name ${_OPTIONS_ARGS})
        jfc_log(STATUS "BLIPBLOP" "${name}")
    endforeach()
    

endfunction()

jfc_parse_arguments(this;is;my;argv;list;
    REQUIRED_OPTIONS
        blar;blam
    OPTIONS
        zip;zop
    REQUIRED_SINGLE_VALUES
        qwer;qwar
    SINGLE_VALUES
        gorgalon;gobaboob
    REQUIRED_LISTS
        nobu;noba
    LISTS
        zippy;zappy
)

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
        set(TAG "DEPENDENCY")

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
# Projects
#================================================================================================
set(JFC_LIBRARY_PROJECT_TEMPLATE_ABSOLUTE_PATH    ${CMAKE_CURRENT_LIST_DIR}/library_project_template.cmake.in)
set(JFC_EXECUTABLE_PROJECT_TEMPLATE_ABSOLUTE_PATH ${CMAKE_CURRENT_LIST_DIR}/executable_project_template.cmake.in)
set(JFC_BUILDINFO_TEMPLATE_ABSOLUTE_PATH          ${CMAKE_CURRENT_LIST_DIR}/buildinfo.h.in)

# Generates a library or executable project.
# See the options in the _required* sets below
# See the output formats in the *_PROJECT_TEMPLATE_ABSOLUTE_PATHs above
# Example usage:
#   jfc_project(executable
#       NAME MyExecutable
#       SOURCE_LIST
#           ${CMAKE_CURRENT_SOURCE_DIR}/main.c
#   )
function(jfc_project aType) # library | executable
    set(TAG "PROJECT")

    set(_required_simple_fields
        "NAME"                        # name of the project
        "VERSION"                     # version of the project (no enforced foramt)
        "DESCRIPTION"                 # description of the project
        "C++_STANDARD"                # minimum ISO language standard required by the C++ compiler.
        "C_STANDARD"                  # minimum ISO language standard required by the C compiler.
    )
    set(_optional_simple_fields 
        ""
    )
    set(_required_list_fields
        "SOURCE_LIST"                 # list of source files
    )
    set(_optional_list_fields
        "PRIVATE_INCLUDE_DIRECTORIES" # Header paths hidden from downstream projects (internal use only)
        "PUBLIC_INCLUDE_DIRECTORIES"  # Header paths accessible (and needed) by downstream projects 
        "LIBRARIES"                   # binary lib files needed by this project (and therefore downstream projects)
    )

    macro(jfc_library_project)
        list(APPEND _required_simple_fields 
            "TYPE"                    # STATIC | DYNAMIC
        )
        set(_project_template_absolute_path "${JFC_LIBRARY_PROJECT_TEMPLATE_ABSOLUTE_PATH}")

        _jfc_project_implementation()
    endmacro()

    macro(jfc_executable_project)
        list(APPEND _optional_list_fields 
            "EXECUTABLE_PARAMETERS"   # list of params. see cmake built in function add_executable
        )
        set(_project_template_absolute_path "${JFC_EXECUTABLE_PROJECT_TEMPLATE_ABSOLUTE_PATH}")

        _jfc_project_implementation()
    endmacro()

    macro(_jfc_project_implementation)
        list(APPEND _all_simple_fields ${_required_simple_fields} ${_optional_simple_fields})
        list(APPEND _all_list_fields   ${_required_list_fields}   ${_optional_list_fields})
        list(APPEND _all_fields        ${_all_simple_fields}      ${_all_list_fields}) 

        set(_parse_mode "PARSE_SIMPLE_FIELDS") # PARSE_SIMPLE_FIELDS | any member of _all_list_fields

        macro(_pop_front)
            list(REMOVE_AT ARGV 0)
            list(LENGTH ARGV _s)
        endmacro()

        list(LENGTH ARGV _s)
        while(_s GREATER 0)
            list(LENGTH ARGV _s)
            list(GET ARGV 0 _item)

            if (_parse_mode STREQUAL "PARSE_SIMPLE_FIELDS")
                list(FIND _required_simple_fields ${_item} _item_is_a_required_field)
                if (_item_is_a_required_field GREATER_EQUAL 0)
                    if (${_s} GREATER 1)
                        list(GET ARGV 1 _value)

                        list(FIND _all_fields ${_value} _value_is_a_field)
                        if (_value_is_a_field GREATER_EQUAL 0)
                            jfc_log(FATAL_ERROR ${TAG} "The field ${_item} requires a value")
                        endif()
                
                        set("${_item}_value" ${_value})

                        _pop_front()
                    else()
                        jfc_log(FATAL_ERROR ${TAG} "${ARGV${_found_index}} requires a value")
                    endif()
                else()
                    list(FIND _all_list_fields ${_item} _item_is_a_list_field)
                    if (_item_is_a_list_field GREATER_EQUAL 0)
                        set(_parse_mode ${_item})
                    else()
                        jfc_log(FATAL_ERROR ${TAG} "\"${_item}\" is a value without a field!")
                    endif()
                endif()

                _pop_front()
            else() # Parsing a list field
                list(FIND _all_fields ${_item} _item_is_a_field)
                if (_item_is_a_field GREATER_EQUAL 0)
                    set(_parse_mode "PARSE_SIMPLE_FIELDS")
                else()
                    list(APPEND "${_parse_mode}" "${_item}")

                    _pop_front()
                endif()
            endif()
        endwhile()

        foreach(_field ${_required_simple_fields})
            if ("${${_field}_value}" STREQUAL "")
                jfc_log(FATAL_ERROR ${TAG} "${_field} is a required field")
            endif()
        endforeach()

        foreach(list ${_required_list_fields})
            set (list_values ${list})
            list(LENGTH ${list_values} _s)

            if ("${_s}" EQUAL 0)
                jfc_log(FATAL_ERROR ${TAG} "${list} is a required list field and is missing or has no entries")
            endif() 
        endforeach()    
        
        foreach(list ${_all_list_fields})
            set (list_values ${list})
            list(LENGTH ${list_values} _s)

            set(_i "0")
            while(${_i} LESS ${_s})
                list(GET "${list_values}" ${_i} value)

                if (NOT ${list}_value)
                    set(${list}_value "${value}")
                else()
                    string(CONCAT ${list}_value "${${list}_value}\n\t" "${value}")
                endif()
            
                MATH(EXPR _i "${_i}+1")
            endwhile()
        endforeach()

        configure_file(${_project_template_absolute_path} "${CMAKE_BINARY_DIR}/${NAME_value}.cmake" @ONLY)

        include("${CMAKE_BINARY_DIR}/${NAME_value}.cmake")

        set(PROJECT_NAME "${PROJECT_NAME}" PARENT_SCOPE) # This makes all project symbols available to the parent scope. I dont know why other symbols do not need to be explicitly promoted
    endmacro()

    list(REMOVE_AT ARGV 0)

    if ("${aType}" STREQUAL "library")
        jfc_library_project("${ARGV}")
    elseif ("${aType}" STREQUAL "executable")
        jfc_executable_project("${ARGV}")
    else()
        jfc_log(FATAL_ERROR ${TAG} "jfc_project unrecognized type: ${aType}. Must be library | executable")
    endif()
endfunction()

#================================================================================================
# Unit tests
#================================================================================================
function(jfc_add_tests)
    set(TAG "TEST")

    jfc_log(WARNING ${TAG} "WIP!")

    set(_OPTIONS_ARGS)
    set(_ONE_VALUE_ARGS C++_STANDARD C_STANDARD)
    set(_MULTI_VALUE_ARGS TEST_SOURCE_LIST)

    cmake_parse_arguments("_ARG" "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGC})

    macro(jfc_assert_required_args aArgType)
        foreach(_one_value ${aArgType})
            if (NOT _ARG_${_one_value})
                jfc_log(FATAL_ERROR ${TAG} "_ARG_${_one_value} is required")
            endif()
        endforeach()
    endmacro()

    jfc_assert_required_args(${_ONE_VALUE_ARGS})
    jfc_assert_required_args(${_MULTI_VALUE_ARGS})

    # get catch2 -> this is dictated by jfccmake, not up to the using project
    # generate the tests.cpp file somehwere in bin dir by grabbing and populating tests.cpp.in in jfccmake module
endfunction()

#================================================================================================
# Documentation: Doxygen
#================================================================================================

#================================================================================================
# Formatting: Clang
#================================================================================================

#================================================================================================
# Formatting: uncrustify
#================================================================================================

#================================================================================================
# Documentation: Readme.md
#================================================================================================

#================================================================================================
# BuildInfo generator
#================================================================================================

#================================================================================================
# SPIRV compiler
#================================================================================================

#================================================================================================
# Resource loader
#================================================================================================
