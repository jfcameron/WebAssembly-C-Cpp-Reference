# © 2018 Joseph Cameron - All Rights Reserved

find_package(CURL REQUIRED)

jfc_set_dependency_symbols(
    INCLUDE_PATHS
        ${CURL_INCLUDE_DIRS}

    LIBRARIES
        ${CURL_LIBRARIES}
)
