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


#ifndef _FTSEVALUATOR_HPP
#define _FTSEVALUATOR_HPP

extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"

	#include "swigrt.h"
}

#include <string>
#include <lua_evaluator.hpp>

#include <Ogre.h>


class FtsEvaluator : public LuaEvaluator
{
public:

	//! Evaluates an expression and stores the result in an Ogre::Vector3 .
	//! If an error occurs, false is returned and the vector is not modified.
	//!
	//! @param expr Lua expression to evaluate to a string.
	//! @param vec Vector which will keep the result.
	//! @return True on success, false on error.
	bool evalVector3(std::string const & expr, Ogre::Vector3 & vec)
	{
		// Get lua to evaluate the expression and store it into an internal
		// global var.
		std::string luaexpr = "_temp_eval = " + expr;

		if( !luaL_dostring(L, luaexpr.c_str()) )
		{
			lua_getglobal( L, "_temp_eval" );

			swig_type_info * pTypeInfo = SWIG_TypeQuery(L, "Ogre::Vector3 *");
			if (pTypeInfo == 0)
				throw std::runtime_error(std::string(
				"Could not find vector type."));

			void * vvect = 0;
			SWIG_Lua_ConvertPtr(L, -1, &vvect, pTypeInfo, 0);
			if(vvect)
			{
				Ogre::Vector3 * vectp = (Ogre::Vector3*)vvect;
				vec = *vectp;
			}
		}

		return false;
	}

};


#endif
