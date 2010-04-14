/*
Copyright (C) 2008-2010 Luis Rodríguez Gil <luis.rodriguez@opendeusto.es>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/


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
