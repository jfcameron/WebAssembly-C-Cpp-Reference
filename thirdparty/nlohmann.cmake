# © 2018 Joseph Cameron - All Rights Reserved

file(COPY "${CMAKE_CURRENT_LIST_DIR}/${PROJECT_NAME}"
    DESTINATION "${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/")

jfc_set_dependency_symbols(
    INCLUDE_PATHS
        "${PROJECT_BINARY_DIR}/include/${PROJECT_NAME}/"
)
