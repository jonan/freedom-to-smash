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


#ifndef _LUAEVALUATOR_HPP
#define _LUAEVALUATOR_HPP

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <string>


//! Evaluates Lua expressions, using the specified
//! Lua state.
//!
class LuaEvaluator
{
	
protected:

	lua_State * L;
	
public:

	LuaEvaluator(lua_State * L)
		: L(L)
	{
	}


	//! Evaluates an expression and stores the result in an integer.
	//! If an error occurs, false is returned and the integer is not modified.
	//!
	//! @param expr Lua expression to evaluate to an integer.
	//! @param integer Integer which will keep the result.
	//! @return True on success, false on error. 
	bool evalInt(std::string const & expr, int & integer)
	{
		double num;

		int result = evalNumber(expr, num);
		
		if(result) 
			integer = static_cast<int>(num);
		
		return result;
	}

	//! Evaluates an expression and stores the result in a double.
	//! If an error occurs, false is returned and the double is not modified.
	//!
	//! @param expr Lua expression to evaluate to a double.
	//! @param number Double which will keep the result.
	//! @return True on success, false on error. 
	bool evalNumber(std::string const & expr, double & number)
	{
		// Get lua to evaluate the expression and store it into an internal
		// global var.
		std::string luaexpr = "_temp_eval = " + expr;

		if( !luaL_dostring(L, luaexpr.c_str()) )
		{
			// Retrieve the internal global var.
			lua_getglobal(L, "_temp_eval");

			// If it is a number as we expect, retrieve it from the stack and
			// return.
			if(lua_isnumber(L, -1))
			{
				number = lua_tonumber(L, -1);
				lua_pop(L, 1);
				return true;
			}
			else
			{
				lua_pop(L, 1);
				return false;
			}
		}
		return false;
	}

	//! Evaluates an expression and stores the result in a string.
	//! If an error occurs, false is returned and the string is not modified.
	//!
	//! @param expr Lua expression to evaluate to a string.
	//! @param str String which will keep the result.
	//! @return True on success, false on error. 
	bool evalString(std::string const & expr, std::string & str)
	{
		// Get lua to evaluate the expression and store it into an internal
		// global var.
		std::string luaexpr = "_temp_eval = " + expr;

		if( !luaL_dostring(L, luaexpr.c_str()) )
		{
			// Retrieve the internal global var.
			lua_getglobal(L, "_temp_eval");

			// If it is a number as we expect, retrieve it from the stack and
			// return.
			if(lua_isstring(L, -1))
			{
				// Lua strings are always zero-terminated but they may have
				// zeros in the middle. We must hence retrieve its length through
				// the function itself and copy the cstring into a std::string.
				// (The original cstring isn't guaranteed to remain valid after
				// it is removed from the stack).

				size_t len;
				char const * cstr = lua_tolstring(L, -1, &len);
				str = std::string(cstr, len);

				lua_pop(L, 1);

				return true;
			}
			else
			{
				lua_pop(L, 1);
				return false;
			}
		}
		return false;
	}

	//! Evaluates an expression and stores the result in a boolean.
	//! If an error occurs, the function returns false and the referenced boolean
	//! is not modified. If the expression is successfuly evaluated (either to
	//! true or false), true will be returned (and the referenced boolean set 
	//! to the appropiate value).
	//!
	//! @param expr Lua expression to evaluate to a bool.
	//! @param str Bool which will keep the result.
	//! @return True on success, false on error. 
	bool evalBool(std::string const & expr, bool & b)
	{
		// Get lua to evaluate the expression and store it into an internal
		// global var.
		std::string luaexpr = "_temp_eval = " + expr;

		if( !luaL_dostring(L, luaexpr.c_str()) )
		{
			// Retrieve the internal global var.
			lua_getglobal(L, "_temp_eval");

			// If it is a boolean as we expect, retrieve it from the stack and
			// return.
			if(lua_isboolean(L, -1))
			{
				b = lua_toboolean(L, -1);
				lua_pop(L, 1);
				return true;
			}
			else
			{
				lua_pop(L, 1);
				return false;
			}
		}

		return false;
	}

};



#endif