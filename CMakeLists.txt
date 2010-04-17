cmake_minimum_required(VERSION 2.8)
project(freedom-to-smash)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Boost REQUIRED)
find_package(ENet REQUIRED)
find_package(Lua51 REQUIRED)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${ENET_INCLUDE_DIR}
  ${LUA_INCLUDE_DIR}
  ${OGRE_INCLUDE_DIRS}
  ${OIS_INCLUDE_DIRS}
  )

if(WIN32)
    add_definitions(-DNOMINMAX)
    link_libraries(winmm.lib)
	link_libraries(ws2_32.lib)
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
if (WIN32)
    file(
      COPY
      ${PROJECT_SOURCE_DIR}/media
      DESTINATION
      ${PROJECT_BINARY_DIR}
      )
else()
    add_custom_command(
      OUTPUT ${PROJECT_BINARY_DIR}/media
      COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_SOURCE_DIR}/media ${PROJECT_BINARY_DIR}/media
      )
    add_custom_target(
      copy-media ALL
      DEPENDS ${PROJECT_BINARY_DIR}/media
      )
endif()

add_subdirectory(src)
