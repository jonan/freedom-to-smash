cmake_minimum_required(VERSION 2.8)
project(freedom-to-smash)

if(WIN32)
    add_definitions(-DNOMINMAX)
    link_libraries(winmm.lib)
endif()

# Copy the configuration files to the binary directory
configure_file("${PROJECT_SOURCE_DIR}/plugins.cfg" "${PROJECT_BINARY_DIR}")
configure_file("${PROJECT_SOURCE_DIR}/resources.cfg" "${PROJECT_BINARY_DIR}")

add_subdirectory(src)
