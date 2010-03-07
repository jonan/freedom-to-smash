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
  scene.cpp
  script.cpp
  server.cpp
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
  scene.hpp
  script.hpp
  server.hpp
  )

if(WIN32)
    if(NOT CYGWIN)
        list(APPEND SRC ${HEADERS})
    endif()
endif()

#set_property(SOURCE ${SRC} PROPERTY COMPILE_FLAGS "-Wall -g")
#set(CMAKE_EXE_LINKER_FLAGS "-lenet")
add_executable(freedom-to-smash ${SRC})
set_target_properties(freedom-to-smash PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
target_link_libraries(
  freedom-to-smash
  ${ENET_LIBRARIES}
  ${LUA_LIBRARIES}
  ${OIS_LIBRARIES}
  ${OGRE_LIBRARIES}
  )
