set(LIBUV_SEARCH_PATH
    "/usr/local"
    "/usr"
    "/opt/local"
    "/Program Files/libuv"
    "/opt/libuv"
)

find_library(
    LIBUV_LIBRARY
    uv
    PATHS
    ${LIBUV_SEARCH_PATH}
    PATH_SUFFIXES
    lib
)

find_path(
    LIBUV_INCLUDE_DIR
    uv.h
    PATHS
    ${LIBUV_SEARCH_PATH}
    PATH_SUFFIXES
    include
)

if (LIBUV_LIBRARY AND LIBUV_INCLUDE_DIR)
    add_library(LibUV::LibUV SHARED IMPORTED)
    set_target_properties(LibUV::LibUV PROPERTIES
        IMPORTED_LOCATION "${LIBUV_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${LIBUV_INCLUDE_DIR}"
    )
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibUV DEFAULT_MSG LIBUV_LIBRARY LIBUV_INCLUDE_DIR)
