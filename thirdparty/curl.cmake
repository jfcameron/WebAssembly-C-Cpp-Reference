# © 2018 Joseph Cameron - All Rights Reserved

find_package(CURL REQUIRED)

jfc_set_dependency_symbols(
    INCLUDE_PATHS
        ${CURL_INCLUDE_DIRS}
        ${CURL_INCLUDE_DIR} #windows madness

    LIBRARIES
        ${CURL_LIBRARIES}
        ${CURL_LIBRARY} #windows madness
)
