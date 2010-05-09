
/* File: wrapping.i */

%module fts

%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
%include "stl.i"

%{

#ifndef IGNORE_FTS_WRAP

#define SWIG_FILE_WITH_INIT


#include "graphics/object.hpp"
#include "graphics/scene.hpp"
#include "physics/object.hpp"
#include "physics/scene.hpp"

#include "object.hpp"
#include "character.hpp"
#include "player.hpp"



%}

%rename(GraphicsObject) graphics::Object;
%include "graphics/object.hpp"

%rename(GraphicsScene) graphics::Scene;
%include "graphics/scene.hpp"

%rename(PhysicsObject) physics::Object;
%include "physics/object.hpp"

%rename(PhysicsScene) physics::Scene;
%include "physics/scene.hpp"


%include "object.hpp"
%include "character.hpp"
%include "player.hpp"



%{

#endif

%}