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

# log all variables visible in the current scope
# useful for identifying and state related bugs
function(jfc_print_all_variables)
    get_cmake_property(cmakevars VARIABLES)
    
    list(SORT cmakevars)
    set(output "")
    
    foreach (cmakevar ${cmakevars})
        string(CONCAT output "${output}" "${cmakevar}=${${cmakevar}}\n")
    endforeach()

    jfc_log(STATUS "Dump" "Called from ${CMAKE_CURRENT_LIST_FILE}...\n${output}")
    jfc_log(STATUS "Dump" "end.")
endfunction()

#================================================================================================
# Utilities
#================================================================================================
# @OPTIONS : booleans
# @SINGLE_VALUES : single values that may be unset
# @REQUIRED_SINGLE_VALUES : single values that must be set
# @LISTS : lists that may be unset
# @REQUIRED_LISTS : lists that must be set
# Wrapper for cmake_parse_arguments that does the busy work of asserting the existence of required args.
# FATAL_ERROR if a required is missing
# the parsed arg list generates a series of variables with names matching your input e.g:
# jfc_parse_arguments(${ARGV}
#   OPTIONS
#       blar
#       blam
#   SINGLE_VALUES
#       zip
#   REQUIRED_SINGLE_VALUES blar
#   LISTS etcetc
#   REQUIRED_LISTS etc
# )
# generates the following variables:
# booleans: blar, blam (TRUE if present in ARGV, FALSE if not)
# single value: zip (may be any value or unset if not present in argv)
# single value: blar (any value, guaranteed to be set after successful call to parse_arguments)
# list: etcetc (must use LIST family of functions to interact with content. unset if not present in ARGV)
# list: etc (must use LIST family of functions to interact with content. guaranteed to be set after successful call to parse_arguments)
function(jfc_parse_arguments)
    set(TAG "jfc_parse_arguments")

    set(NULL)
    set(_MULTI_VALUE_ARGS
        OPTIONS    
        SINGLE_VALUES          
        LISTS 
        REQUIRED_SINGLE_VALUES 
        REQUIRED_LISTS)

    set(_argv_passthrough)
    foreach(_arg ${ARGV})
        list(FIND _MULTI_VALUE_ARGS ${_arg} _item_is_a_name)

        if (_item_is_a_name GREATER_EQUAL 0)
            break()
        endif()

        list(APPEND _argv_passthrough ${_arg})
    endforeach()

    list (LENGTH _argv_passthrough _s)
    if (_s EQUAL 0)
        jfc_log(FATAL_ERROR ${TAG} "nothing to parse! Did you forget to prepend $\{ARGV\} to your list of requirements?")
    endif()

    cmake_parse_arguments("_ARG" "${NULL}" "${NULL}" "${_MULTI_VALUE_ARGS}" ${ARGN})

    macro(_promote_args_to_parent_scope argType bNoPrefix)
        if (NOT ${bNoPrefix})
            set(_prefix "_ARG_")
        endif()

        foreach(name ${${argType}})
            list(LENGTH _ARG_${name} _s)

            if (_s GREATER 0)
                set(${_prefix}${name} "${_ARG_${name}}" PARENT_SCOPE)

                if (NOT ${bNoPrefix})
                    jfc_log(STATUS "${name}" "${_ARG_${name}}") #The leak is revealedhere. There is sometghing wrong with this function
                endif() 
            endif()
        endforeach()
    endmacro()

    # Generate & assert requireds
    function(_required_args_imp)
        set(_ONE_VALUE_ARGS   "${_ARG_REQUIRED_SINGLE_VALUES}")
        set(_MULTI_VALUE_ARGS "${_ARG_REQUIRED_LISTS}"        )

        set(_ONE_VALUE_ARGS   "${_ARG_REQUIRED_SINGLE_VALUES}" PARENT_SCOPE) # Must be promoted to index output of this function in parent function
        set(_MULTI_VALUE_ARGS "${_ARG_REQUIRED_LISTS}"         PARENT_SCOPE)

        cmake_parse_arguments("_ARG" "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN})

        macro(_validate_and_promote_args_to_parent_scope argType)
            foreach(name ${${argType}})
                list(LENGTH _ARG_${name} _s)

                if (_s GREATER 0)
                    set(_i "0")

                    while(${_i} LESS ${_s})
                        list(GET "_ARG_${name}" ${_i} value)

                        MATH(EXPR _i "${_i}+1")
                    endwhile()
                else()
                    jfc_log(FATAL_ERROR ${TAG} "Required arg \"${name}\" is missing or contains no values!")
                endif()
            endforeach()

            _promote_args_to_parent_scope("${argType}" FALSE)
        endmacro()

        _validate_and_promote_args_to_parent_scope(_ONE_VALUE_ARGS)
        _validate_and_promote_args_to_parent_scope(_MULTI_VALUE_ARGS)
    endfunction()
    _required_args_imp(${_argv_passthrough})

    _promote_args_to_parent_scope(_ONE_VALUE_ARGS TRUE)
    _promote_args_to_parent_scope(_MULTI_VALUE_ARGS TRUE)

    # Generate optionals
    function(_optional_args_imp)
        set(_OPTIONS_ARGS     "${_ARG_OPTIONS}")
        set(_ONE_VALUE_ARGS   "${_ARG_SINGLE_VALUES}")
        set(_MULTI_VALUE_ARGS "${_ARG_LISTS}")

        set(_OPTIONS_ARGS     "${_ARG_OPTIONS}"       PARENT_SCOPE)
        set(_ONE_VALUE_ARGS   "${_ARG_SINGLE_VALUES}" PARENT_SCOPE)
        set(_MULTI_VALUE_ARGS "${_ARG_LISTS}"         PARENT_SCOPE)

        cmake_parse_arguments("_ARG" "${_OPTIONS_ARGS}" "${_ONE_VALUE_ARGS}" "${_MULTI_VALUE_ARGS}" ${ARGN})

        _promote_args_to_parent_scope(_OPTIONS_ARGS FALSE)
        _promote_args_to_parent_scope(_ONE_VALUE_ARGS FALSE)
        _promote_args_to_parent_scope(_MULTI_VALUE_ARGS FALSE)
    endfunction()
    _optional_args_imp(${_argv_passthrough})

    _promote_args_to_parent_scope(_OPTIONS_ARGS TRUE)
    _promote_args_to_parent_scope(_ONE_VALUE_ARGS TRUE)
    _promote_args_to_parent_scope(_MULTI_VALUE_ARGS TRUE)
endfunction()

#
# namespace for directory manipulation
# contained commands are selected via value of ARGV0
# e.g: jfc_directory(basename "/the/path/to/dir" currentdirectorybasename)
#
function(jfc_directory)
    set(TAG "directory")

    #
    # given a directory path @aPath, writes the name of the current directory to identifier with name @aOutput
    # (think: basename BSD utility)
    # eg:
    # jfc_directory(basename "/path/to/mydirectory" output)
    # message(STATUS "${output}")
    # result:
    # mydirectory
    #
    macro(_basename aPath aOutput)
        set(TAG "basename")

        string(FIND ${aPath} "/" _i REVERSE) # There maybe a posix assumption here!

        if (_i EQUAL -1)
            jfc_log(FATAL_ERROR ${TAG} "Path is malformed. Could not determine basename")
        endif()

        math(EXPR _i "${_i}+1")

        string(SUBSTRING ${aPath} ${_i} -1 ${aOutput})

        set (${aOutput} ${${aOutput}} PARENT_SCOPE)
    endmacro()

    if (ARGN LESS_EQUAL 0)
        jfc_log(FATAL_ERROR ${TAG} "requires at least one param to determine command to run")
    endif()

    list(REMOVE_AT ARGV 0)

    string(TOLOWER "${ARGV0}" ARGV0)

    if ("${ARGV0}" STREQUAL "basename")
        _basename(${ARGV})
    endif()
endfunction()

# Check if a program is installed on the system. Log and throw if it is not
function(jfc_require_program aProgramName)
    set(TAG "require program")

    string(TOUPPER "${aProgramName}" _UpperProgramName)

    find_program(${_UpperProgramName} NAMES "${aProgramName}")

    if (${_UpperProgramName} STREQUAL "${_UpperProgramName}-NOTFOUND")
        jfc_log(FATAL_ERROR ${TAG} "required program \"${aProgramName}\" could not be found!")
    endif()
endfunction()

# Call git commands, throwing if there is an error
# @COMMAND the command to run e.g: status
# @OUTPUT the symbol this function will assign the standard out result of the git command to
# example usage:
# jfc_git(COMMAND rev-parse HEAD
#   OUTPUT theCurrentCommitHash)
#
# message(STATUS "${theCurrentCommitHash}") # the current commit's hash
#
function(jfc_git)
    set(TAG "git")

    jfc_require_program("git")

    jfc_parse_arguments(${ARGV}
        REQUIRED_LISTS
            COMMAND
        SINGLE_VALUES
            OUTPUT
    )

    execute_process(COMMAND git ${COMMAND}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE _return_value
        OUTPUT_VARIABLE _output_value
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    if (_return_value GREATER 0)
        string(REPLACE ";" " " aGitCommand "${COMMAND}")

        jfc_log(FATAL_ERROR ${TAG} "the command \"git ${aGitCommand}\" failed with return value of \"${_return_value}\"")
    endif()

    set(${OUTPUT} "${_output_value}" PARENT_SCOPE)
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
#            _add_dependency("MyCoolLib")
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
    function(_add_dependency aName)
        set(TAG "dependency")

        if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${aName}.cmake)
            jfc_log(FATAL_ERROR ${TAG} "${CMAKE_CURRENT_SOURCE_DIR}/${aName}.cmake does not exist. This is required to instruct the loader how to build dependency \"${aName}\".")
        endif()

        jfc_git(COMMAND submodule update --init -- ${CMAKE_CURRENT_SOURCE_DIR}/${aName})

        set(JFC_DEPENDENCY_NAME "${aName}")

        include("${aName}.cmake")

        # TODO: these should be promoted

        if (NOT DEFINED ${aName}_LIBRARIES)
            jfc_log(WARNING ${TAG} "${aName}.cmake did not define a variable \"${aName}_LIBRARIES\". Is it header only?")
        endif()

        if (NOT DEFINED ${aName}_INCLUDE_DIR)
            jfc_log(FATAL_ERROR ${TAG} "${aName}.cmake did not define a variable \"${aName}_INCLUDE_DIR\".")
        endif()

        jfc_log(STATUS ${TAG} "Done processing submodule dependency \"${aName}\". ${aName}_INCLUDE_DIR: ${${aName}_INCLUDE_DIR}, ${aName}_LIBRARIES: ${${aName}_LIBRARIES}")
    endfunction()

    MATH(EXPR ARGC "${ARGC}-1")

    foreach(_i RANGE ${ARGC})
        _add_dependency("${ARGV${_i}}")
    endforeach()
endfunction()

#================================================================================================
# Projects
#================================================================================================
set(JFC_LIBRARY_PROJECT_TEMPLATE_ABSOLUTE_PATH    ${CMAKE_CURRENT_LIST_DIR}/library_project_template.cmake.in)
set(JFC_EXECUTABLE_PROJECT_TEMPLATE_ABSOLUTE_PATH ${CMAKE_CURRENT_LIST_DIR}/executable_project_template.cmake.in)
set(JFC_BUILDINFO_TEMPLATE_ABSOLUTE_PATH          ${CMAKE_CURRENT_LIST_DIR}/buildinfo.h.in)

# TODO: Simplify implementation: make use of jfc_parse_arguments
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

    macro(_library_project)
        list(APPEND _required_simple_fields 
            "TYPE"                    # STATIC | DYNAMIC
        )
        set(_project_template_absolute_path "${JFC_LIBRARY_PROJECT_TEMPLATE_ABSOLUTE_PATH}")

        jfc_parse_arguments(${ARGV}
            REQUIRED_SINGLE_VALUES ${_required_simple_fields} #no leaks
            SINGLE_VALUES          ${_optional_simple_fields} #no leaks
            REQUIRED_LISTS         ${_required_list_fields}   #no leaks
            LISTS "PRIVATE_INCLUDE_DIRECTORIES" "PUBLIC_INCLUDE_DIRECTORIES" "LIBRARIES" #"PRIVATE_INCLUDE_DIRECTORIES" #"PUBLIC_INCLUDE_DIRECTORIES" #"LIBRARIES" # oh _no_....
        )

        #jfc_print_all_variables()

        #jfc_log(STATUS ${TAG} "== Current project: ${NAME} ==")

        _jfc_project_implementation()
    endmacro()

    macro(_executable_project)
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

        # TODO: think about how to promote all project_* variables.
        set(PROJECT_NAME       "${PROJECT_NAME}"       PARENT_SCOPE) # Project vars must be promoted to be accessible in call scope
        set(PROJECT_BINARY_DIR "${PROJECT_BINARY_DIR}" PARENT_SCOPE)
    endmacro()

    list(REMOVE_AT ARGV 0)

    if ("${aType}" STREQUAL "library")
        _library_project("${ARGV}")
    elseif ("${aType}" STREQUAL "executable")
        _executable_project("${ARGV}")
    else()
        jfc_log(FATAL_ERROR ${TAG} "jfc_project unrecognized type: ${aType}. Must be library | executable")
    endif()
endfunction()

#================================================================================================
# Documentation: Readme.md
#================================================================================================
set(JFC_README_TEMPLATE_ABSOLUTE_PATH ${CMAKE_CURRENT_LIST_DIR}/README.md.in)
set(JFC_PROJECT_ROOT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Generates a readme.md, useful for github projects
# @DESCRIPTION required, description of the project
function(jfc_generate_readme_md)
    set(TAG "readme")
    
    jfc_parse_arguments(${ARGV}
        REQUIRED_SINGLE_VALUES
            BRIEF
        SINGLE_VALUES
            DESCRIPTION
        LISTS
            IMAGES
    )

    jfc_directory(BASENAME ${JFC_PROJECT_ROOT_DIRECTORY} REPO_NAME)

    foreach(_current_url ${IMAGES})
        string(CONFIGURE "<img src=\"@_current_url@\" width=\"100%\">" _currentImage)
        
        string(CONCAT IMAGES_OUTPUT "${IMAGES_OUTPUT}" "${_currentImage}")
    endforeach()
    
    configure_file(${JFC_README_TEMPLATE_ABSOLUTE_PATH} "${JFC_PROJECT_ROOT_DIRECTORY}/README.md" @ONLY)

endfunction()

#================================================================================================
# Unit tests
#================================================================================================
# @TEST_SOURCE_LIST
# @C++_STANDARD required iso langauge standard for C++ 
# @C_STANDARD required iso language standard for C
function(jfc_add_tests)
    set(TAG "TEST")

    jfc_log(STATUS ${TAG} "this is not completed at all")

    jfc_parse_arguments(${ARGV}
        REQUIRED_SINGLE_VALUES
            C++_STANDARD
            C_STANDARD
            TEST_SOURCE_LIST
    )

    # get catch2 -> this is dictated by jfccmake, not up to the using project
    # generate the tests.cpp file somehwere in bin dir by grabbing and populating tests.cpp.in in jfccmake module
endfunction()

#================================================================================================
# Documentation: Doxygen
#================================================================================================
# TODO: verify, consider changing
function(jfc_generate_documentation_doxygen)
    find_program(DOXYGEN doxygen)

    if(NOT DOXYGEN)
        jfc_log(FATAL_ERROR ${TAG} "doxygen not found! It is required to generate documentation.")
    else()
        set(DOXY_CONFIG_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
        set(DOXY_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")
        set(DOXY_CONFIG_FILENAME "doxy.config")

        configure_file(${DOXY_CONFIG_DIR}/${DOXY_CONFIG_FILENAME}.in 
            ${CMAKE_CURRENT_SOURCE_DIR}/${DOXY_CONFIG_FILENAME} @ONLY)

        execute_process(COMMAND ${DOXYGEN} ${DOXY_CONFIG_FILENAME}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE DOXYGEN_RETURN_VALUE
            OUTPUT_VARIABLE DOXYGEN_ERRORS)

        if (DOXYGEN_RETURN_VALUE)
            jfc_log(FATAL_ERROR ${TAG} "Doxygen failed: ${DOXYGEN_ERRORS}")
        else()
            jfc_log(STATUS ${TAG} "Doxygen successfully completed")
        endif()
        
        file(REMOVE "${CMAKE_CURRENT_SOURCE_DIR}/${DOXY_CONFIG_FILENAME}")
    endif()
endfunction()

#================================================================================================
# Formatting: uncrustify
#================================================================================================
# TODO: type list with default fallback
# TODO: where should the uncrustify settings come from? fallback + override?
function(jfc_format_code_uncrustify aDirectory)
    set(TAG "format")

    if (NOT IS_DIRECTORY ${aDirectory})
        jfc_log(FATAL_ERROR ${TAG} "${aDirectory} does not exist or is not a directory.")
    endif()

    set(FORMATTER_NAME "uncrustify")

    find_program(FORMATTER "${FORMATTER_NAME}")

    if(NOT FORMATTER)
        jfc_log(FATAL_ERROR ${TAG} "${FORMATTER_NAME} not found! It is required to format the source code.")
    else()
        file(GLOB_RECURSE JFC_SOURCES
            ${aDirectory}/*.h   ${aDirectory}/*.hpp
            ${aDirectory}/*.cpp ${aDirectory}/*.cxx
            ${aDirectory}/*.c)

    execute_process(COMMAND ${FORMATTER} files ${JFC_SOURCES} --no-backup -c ${CMAKE_SOURCE_DIR}/.uncrustify #-l CPP
        WORKING_DIRECTORY ${aDirectory}
        RESULT_VARIABLE FORMATTER_RETURN_VALUE
        OUTPUT_VARIABLE FORMATTER_ERRORS)
    endif()
endfunction()

#================================================================================================
# Formatting: Clang
#================================================================================================
# TODO: where should the clang settings come from? fallback + override?
function(jfc_format_code_clang) 
    set(TAG "format")

    jfc_require_program("uncrustify")

    jfc_log(STATUS ${TAG} "this is not completed at all")
endfunction()

#================================================================================================
# SPIRV compiler
#================================================================================================
# Todo: verify
function(jfc_compile_SPIRV_shader_glsl)
    find_program(GLSL_COMPILER glslangValidator)

    set(TAG "Shader compiling stage")

    if(NOT GLSL_COMPILER)
        jfc_log(FATAL_ERROR ${TAG} "glslangValidator not found! It is required to compile GLSL source to SPIR-V.")
    endif()

    file(GLOB_RECURSE GLSL_SOURCE_FILES 
        *.vert *.tesc *.tese *.geom *.frag *.comp)

    foreach(GLSL ${GLSL_SOURCE_FILES})
        get_filename_component(FILE_NAME ${GLSL} NAME)

        set(SPIRV "${CMAKE_SOURCE_DIR}/build/shaders/${FILE_NAME}.spv")

        make_directory("${CMAKE_SOURCE_DIR}/build/shaders/")

        execute_process(COMMAND ${GLSL_COMPILER} -V ${GLSL} -o ${SPIRV}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GLSL_COMPILER_RETURN_VALUE
            OUTPUT_VARIABLE GLSL_COMPILER_ERRORS)

        if (GLSL_COMPILER_RETURN_VALUE)
            jfc_log(FATAL_ERROR ${TAG} "\"${FILE_NAME}\" failed to compile: ${GLSL_COMPILER_ERRORS}")
        else()
            jfc_log(STATUS ${TAG} "\"${FILE_NAME}\" successfully compiled")
        endif()
    endforeach(GLSL)
endfunction()

#================================================================================================
# Emscripten index.html generator
#================================================================================================
set(JFC_EMSCRIPTEN_INDEX_HTML_TEMPLATE_ABSOLUTE_PATH ${CMAKE_CURRENT_LIST_DIR}/emscripten_index_template.html.in)

function(jfc_emscripten_generate_index_html_for_current_project)
    set(TAG "html")

    configure_file(${JFC_EMSCRIPTEN_INDEX_HTML_TEMPLATE_ABSOLUTE_PATH} "${PROJECT_BINARY_DIR}/index.html" @ONLY)
endfunction()

#================================================================================================
# Resource loader
#================================================================================================
#
function(jfc_resource)
    jfc_log(FATAL_ERROR "blarblar" "resource must be implemented")

    #
    function(jfc_export_resource aResourceDirectory)
        set(TAG "Resource exporter")

        #[[if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${aResourceDirectory}" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${aResourceDirectory}")
            jfc_log(STATUS ${TAG} "Exporting ${aResourceDirectory}")

            file(COPY "${aResourceDirectory}" 
                DESTINATION ${CMAKE_SOURCE_DIR}/build/)
        else()
            jfc_log(FATAL_ERROR ${TAG} "\"${aResourceDirectory}\" does not exist or is not a directory.")
        endif()]]

        jfc_log(FATAL_ERROR ${TAG} "This is not implemented.")
    endfunction()

    #
    function(jfc_compile_resources)
        jfc_parse_arguments(${ARGV}
            REQUIRED_LISTS
                FILES
        )

        set(TAG "resource compile")

        function(_compile_resource aFile)
            file(READ "${aFile}" bytes HEX)
    
            string(REGEX REPLACE "(..)" "0x\\1, " bytes "${bytes}")

            string(FIND "${bytes}" ", " _i REVERSE)

            string(SUBSTRING "${bytes}" 0 ${_i} bytes)
    
            message("${bytes}")
        endfunction()

        foreach(_file ${FILES})
            _compile_resource("${_file}")
        endforeach()

        jfc_log(FATAL_ERROR ${TAG} "This is not implemented.")
    endfunction()
endfunction()


