set(
  SRC
  physics/collision_scene.cpp
  animated_object.cpp
  battle_ground.cpp
  boot.cpp
  character.cpp
  input.cpp
  main.cpp
  object.cpp
  platform.cpp
  player.cpp
  scene.cpp
  script.cpp
  server.cpp
  )

set(
  HEADERS
  physics/collision_scene.hpp
  animated_object.hpp
  battle_ground.hpp
  boot.hpp
  character.hpp
  input.hpp
  object.hpp
  platform.hpp
  player.hpp
  scene.hpp
  script.hpp
  server.hpp
  )

if(WIN32)
    if(NOT CYGWIN)
        list(APPEND SRC ${HEADERS})
    endif()
endif()

add_executable(freedom-to-smash ${SRC})
set_target_properties(freedom-to-smash PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_link_libraries(
  freedom-to-smash
  ${BULLET_LIBRARIES}
  ${ENET_LIBRARIES}
  ${LUA_LIBRARIES}
  ${OIS_LIBRARIES}
  ${OGRE_LIBRARIES}
  ${OPENAL_LIBRARY}
  )
