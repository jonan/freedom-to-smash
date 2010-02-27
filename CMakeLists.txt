cmake_minimum_required(VERSION 2.8)
project(freedom-to-smash)

if(WIN32)
    add_definitions(-DNOMINMAX)
    link_libraries(winmm.lib)
endif()

# Copy the configuration files to the binary directory
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/plugins.cfg
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/plugins.cfg ${PROJECT_BINARY_DIR}/plugins.cfg
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/plugins.cfg
  )
add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/resources.cfg
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/resources.cfg ${PROJECT_BINARY_DIR}/resources.cfg
  MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/resources.cfg
  )
add_custom_target(
  copy-config ALL
  DEPENDS ${PROJECT_BINARY_DIR}/plugins.cfg ${PROJECT_BINARY_DIR}/resources.cfg
  )

# Copy the media files to the binary directory
file(
  COPY
  "${PROJECT_SOURCE_DIR}/media"
  DESTINATION
  "${PROJECT_BINARY_DIR}"
  )

add_subdirectory(src)
