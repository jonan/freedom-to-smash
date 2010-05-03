cmake_minimum_required(VERSION 2.6)
project(freedom-to-smash)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Necessary libraries
find_package(Boost REQUIRED)
find_package(Lua51 REQUIRED)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)
find_package(OpenAL REQUIRED)
find_package(SDL REQUIRED)

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/bullet
  ${PROJECT_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIRS}
  ${LUA_INCLUDE_DIR}
  ${OGRE_INCLUDE_DIRS}
  ${OIS_INCLUDE_DIRS}
  ${OPENAL_INCLUDE_DIR}
  ${SDL_INCLUDE_DIR}
  )

# Optional libraries
find_package(ENet)

if(ENET_FOUND)
    include_directories(${ENET_INCLUDE_DIR})
endif()

if(WIN32)
    add_definitions(-DNOMINMAX)
    link_libraries(winmm.lib)
    link_libraries(ws2_32.lib)
endif()

# Copy the configuration files to the binary directory
if(WIN32)
    add_custom_command(
      OUTPUT ${PROJECT_BINARY_DIR}/plugins.cfg
      COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/plugins.cfg.win32 ${PROJECT_BINARY_DIR}/plugins.cfg
      MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/plugins.cfg.win32
      )
else()
    add_custom_command(
      OUTPUT ${PROJECT_BINARY_DIR}/plugins.cfg
      COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/plugins.cfg.unix ${PROJECT_BINARY_DIR}/plugins.cfg
      MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/plugins.cfg.unix
      )
endif()
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
if(WIN32)
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

add_subdirectory(bullet)
set(
  BULLET_LIBRARIES
  BulletCollision
  BulletDynamics
  BulletMultiThreaded
  BulletSoftBody
  LinearMath
  )

add_subdirectory(hydrax)
set(HYDRAX_LIBRARIES Hydrax)

add_subdirectory(skyx)
set(SKYX_LIBRARIES SkyX)

add_subdirectory(src)
