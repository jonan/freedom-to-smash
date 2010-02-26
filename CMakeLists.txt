cmake_minimum_required(VERSION 2.8)
project(freedom-to-smash)

if(WIN32)
    add_definitions(-DNOMINMAX)
    link_libraries(winmm.lib)
endif()

# Copy the configuration files to the binary directory
file(
  COPY
  "${PROJECT_SOURCE_DIR}/plugins.cfg"
  "${PROJECT_SOURCE_DIR}/resources.cfg"
  DESTINATION
  "${PROJECT_BINARY_DIR}"
  )

# Copy the media files to the binary directory
file(
  COPY
  "${PROJECT_SOURCE_DIR}/media"
  DESTINATION
  "${PROJECT_BINARY_DIR}"
  )

add_subdirectory(src)
