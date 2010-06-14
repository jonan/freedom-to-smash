cmake_minimum_required(VERSION 2.6)
project(freedom-to-smash)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Necessary libraries
find_package(Boost REQUIRED)
find_package(Lua51 REQUIRED)
find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)
find_package(OpenAL REQUIRED)

if(NOT WIN32)
    pkg_check_modules(VORBIS REQUIRED vorbisfile)
else()
    set(VORBIS_INCLUDE_DIRS .)
    set(VORBIS_LIBRARIES .)
endif()

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/bullet
  ${PROJECT_SOURCE_DIR}/quick_gui/include
  ${PROJECT_SOURCE_DIR}/src
  ${Boost_INCLUDE_DIRS}
  ${LUA_INCLUDE_DIR}
  ${OGRE_INCLUDE_DIRS}
  ${OIS_INCLUDE_DIRS}
  ${OPENAL_INCLUDE_DIR}
  ${VORBIS_INCLUDE_DIRS}
  )

if(WIN32)
    add_definitions(-DNOMINMAX -DHYDRAX_LIB -DSKYX_LIB -DQUICKGUI_EXPORTS)
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

# Copy the mene sheets to the binary directory
set(
  MENU_SHEETS
  main_menu
  )
foreach(SHEET ${MENU_SHEETS})
  add_custom_command(
    OUTPUT ${PROJECT_BINARY_DIR}/menu_sheets/${SHEET}
    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/menu_sheets/${SHEET} ${PROJECT_BINARY_DIR}/menu_sheets/${SHEET}
    MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/menu_sheets/${SHEET}
    )
    add_custom_target(
      copy-menu-sheets ALL
      DEPENDS ${PROJECT_BINARY_DIR}/menu_sheets/${SHEET}
      )
endforeach()

add_subdirectory(bullet)
set(
  BULLET_LIBRARIES
  BulletSoftBody
  BulletDynamics
  BulletCollision
  BulletMultiThreaded
  LinearMath
  )

add_subdirectory(hydrax)
set(HYDRAX_LIBRARIES Hydrax)

add_subdirectory(quick_gui)
set(QUICK_GUI_LIBRARIES QuickGUI)

add_subdirectory(skyx)
set(SKYX_LIBRARIES SkyX)

add_subdirectory(src)
