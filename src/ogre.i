
/* File: wrapping.i */

%module ogre

%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"
%include "stl.i"

%{

#ifndef IGNORE_FTS_WRAP

#define SWIG_FILE_WITH_INIT


#include <Ogre.h>

using namespace Ogre;



%}

#define _OgreExport 

typedef std::string String;
typedef float Real;


%include "OgreVector3.h"



%{

#endif

%}