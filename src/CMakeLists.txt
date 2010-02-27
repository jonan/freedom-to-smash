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
  server.hpp
  )

if(WIN32)
    if(NOT CYGWIN)
        list(APPEND SRC ${HEADERS})
    endif()
endif()

add_definitions(-DOGRE_GUI_GLX -DOGRE_CONFIG_LITTLE_ENDIAN)

set_property(SOURCE ${SRC} PROPERTY COMPILE_FLAGS "-Wall -g -I/usr/include/OGRE -I/usr/include/OIS")
set(CMAKE_EXE_LINKER_FLAGS "-lOgreMain -lOIS -lenet")
add_executable(freedom-to-smash ${SRC})
set_target_properties(freedom-to-smash PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
