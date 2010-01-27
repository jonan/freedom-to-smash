set(
  SRC
  battle_ground.cpp
  boot.cpp
  character.cpp
  collision_box.cpp
  input.cpp
  main.cpp
  object.cpp
  platform.cpp
  server.cpp
  )

add_definitions(-DOGRE_GUI_GLX -DOGRE_CONFIG_LITTLE_ENDIAN)

set_property(SOURCE ${SRC} PROPERTY COMPILE_FLAGS "-Wall -g -I/usr/include/OGRE -I/usr/include/OIS")
set(CMAKE_EXE_LINKER_FLAGS "-lOgreMain -lOIS -lenet")
add_executable(freedom-to-smash ${SRC})

