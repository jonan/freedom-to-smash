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
  server.cpp
  
  luautils.cpp
  lua_evaluator.cpp
  lua_engine.cpp
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
  server.hpp
  
  swigrt.h
  luautils.hpp
  lua_evaluator.hpp
  lua_engine.hpp
  )
  
  
SOURCE_GROUP(Lua FILES luautils.cpp luautils.hpp lua_evaluator.cpp lua_evaluator.hpp lua_engine.cpp lua_engine.hpp)
SOURCE_GROUP(Lua\\Generated FILES swigrt.h)

  
if(WIN32)
    if(NOT CYGWIN)
        list(APPEND SRC ${HEADERS})
    endif()
endif()

add_executable(freedom-to-smash ${SRC})
set_target_properties(freedom-to-smash PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_link_libraries(
  freedom-to-smash
  ${ENET_LIBRARIES}
  ${LUA_LIBRARIES}
  ${OIS_LIBRARIES}
  ${OGRE_LIBRARIES}
  ${OPENAL_LIBRARY}
  )
