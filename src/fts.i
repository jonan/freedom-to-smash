
/* File: wrapping.i */

%module fts

%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
%include "stl.i"

%{

#ifndef IGNORE_FTS_WRAP

#define SWIG_FILE_WITH_INIT


#include "object.hpp"
#include "character.hpp"
#include "player.hpp"

%}


%include "graphics/object.hpp"
%include "graphics/scene.hpp"
%include "physics/object.hpp"
%include "physics/scene.hpp"

%include "object.hpp"
%include "character.hpp"
%include "player.hpp"



%{

#endif

%}