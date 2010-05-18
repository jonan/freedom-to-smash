set(
  SRC
  graphics/object.cpp
  graphics/scene.cpp
  gui/gui.cpp
  physics/debug_drawer.cpp
  physics/object.cpp
  physics/scene.cpp
  physics/shapes_manager.cpp
  battle_ground.cpp
  boot.cpp
  character.cpp
  input.cpp
  main.cpp
  lua_engine.cpp
  lua_evaluator.cpp
  luautils.cpp
  object.cpp
  platform.cpp
  player.cpp
  scene.cpp
  Scheduler.cpp
  ScheduledItem.cpp
  script.cpp
  )

set(
  HEADERS
  graphics/object.hpp
  graphics/scene.hpp
  gui/gui.hpp
  physics/converter_functions.hpp
  physics/debug_drawer.hpp
  physics/object.hpp
  physics/scene.hpp
  physics/shapes_manager.hpp
  battle_ground.hpp
  boot.hpp
  character.hpp
  input.hpp
  object.hpp
  platform.hpp
  player.hpp
  scene.hpp
  script.hpp
  util.hpp

  Scheduler.h
  ScheduledItem.h
  ITask.h
  server.hpp

  swigrt.h
  luautils.hpp
  lua_evaluator.hpp
  lua_engine.hpp
  )

source_group(Lua FILES luautils.cpp luautils.hpp lua_evaluator.cpp lua_evaluator.hpp lua_engine.cpp lua_engine.hpp)
source_group(Lua\\Generated FILES swigrt.h)
source_group(Scheduler FILES ITask.h Scheduler.h Scheduler.cpp ScheduledItem.h ScheduledItem.cpp)
source_group(Graphics REGULAR_EXPRESSION graphics/.*)
source_group(Physics REGULAR_EXPRESSION physics/.*)

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
  ${BULLET_LIBRARIES}
  ${ENET_LIBRARIES}
  ${HYDRAX_LIBRARIES}
  ${LUA_LIBRARIES}
  ${OIS_LIBRARIES}
  ${OGRE_LIBRARIES}
  ${OPENAL_LIBRARY}
  ${QUICK_GUI_LIBRARIES}
  ${SDL_LIBRARY}
  ${SKYX_LIBRARIES}
  )
# Link optional libraries
if(ENET_FOUND)
    target_link_libraries(freedom-to-smash ${ENET_LIBRARIES})
endif()
