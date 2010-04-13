

#ifndef _LUA_UTILS_H
#define _LUA_UTILS_H

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <Ogre.h>


Ogre::Vector3 lua_vectorexpr( lua_State * L, const char * expr, 
							 Ogre::Vector3 const & def );





#endif
