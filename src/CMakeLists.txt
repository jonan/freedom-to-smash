set(
  SRC
  animated_object.cpp
  battle_ground.cpp
  boot.cpp
  character.cpp
  collision_box.cpp
  input.cpp
  main.cpp
  object.cpp
  platform.cpp
  player.cpp
  scene.cpp
  script.cpp
  audio/soundmanager.cpp
  audio/soundloader.cpp
  audio/soundresources.cpp
  audio/soundbuffer.cpp
  )

set(
  HEADERS
  animated_object.hpp
  battle_ground.hpp
  boot.hpp
  character.hpp
  collision_box.hpp
  input.hpp
  object.hpp
  platform.hpp
  player.hpp
  scene.hpp
  script.hpp
  audio/soundmanager.hpp
  audio/soundloader.hpp
  audio/soundresources.hpp
  audio/soundbuffer.hpp
  )

# Compile the network code only if ENet was found
if(ENET_FOUND)
    list(APPEND SRC server.cpp)
    list(APPEND HEADERS server.hpp)
endif()

if(WIN32)
    if(NOT CYGWIN)
        list(APPEND SRC ${HEADERS})
    endif()
endif()

add_executable(freedom-to-smash ${SRC})
set_target_properties(freedom-to-smash PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
# Link necessary libraries
target_link_libraries(
  freedom-to-smash
  ${ENET_LIBRARIES}
  ${LUA_LIBRARIES}
  ${OIS_LIBRARIES}
  ${OGRE_LIBRARIES}
  ${OPENAL_LIBRARY}
  ${SDL_LIBRARY}
  )
# Link optional libraries
if(ENET_FOUND)
    target_link_libraries(freedom-to-smash ${ENET_LIBRARIES})
endif()
