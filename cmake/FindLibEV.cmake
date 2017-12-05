set(LIBEV_SEARCH_PATH
    "/usr/local"
    "/usr"
    "/opt/local"
    "/Program Files/libev"
    "/opt/libev"
)

find_library(
    LIBEV_LIBRARY
    ev
    PATHS
    ${LIBEV_SEARCH_PATH}
    PATH_SUFFIXES
    lib
)

find_path(
    LIBEV_INCLUDE_DIR
    ev.h
    PATHS
    ${LIBEV_SEARCH_PATH}
    PATH_SUFFIXES
    include
)

if (LIBEV_LIBRARY AND LIBEV_INCLUDE_DIR)
    add_library(LibEV::LibEV SHARED IMPORTED)
    set_target_properties(LibEV::LibEV PROPERTIES
        IMPORTED_LOCATION "${LIBEV_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${LIBEV_INCLUDE_DIR}"
    )
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibEV DEFAULT_MSG LIBEV_LIBRARY LIBEV_INCLUDE_DIR)
