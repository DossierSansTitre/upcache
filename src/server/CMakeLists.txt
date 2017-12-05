find_package(LibUV REQUIRED)

file(GLOB_RECURSE SOURCES "*.c")
add_executable(upcached ${SOURCES})
target_include_directories(upcached PRIVATE ".")
target_link_libraries(upcached LibUV::LibUV)
