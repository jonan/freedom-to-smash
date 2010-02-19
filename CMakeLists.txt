cmake_minimum_required(VERSION 2.8)
project(freedom-to-smash)

if(WIN32)
    add_definitions(-DNOMINMAX)
    link_libraries(winmm.lib)
endif()

add_subdirectory(src)
