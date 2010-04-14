/*
Copyright (C) 2008-2010 Luis Rodr�guez Gil <luis.rodriguez@opendeusto.es>

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

#ifndef _LUAENGINE_H
#define _LUAENGINE_H

#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <stdexcept>


#include "swigrt.h"


extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}


//! Provides several utility methods to make Lua integration
//! and usage easier from C++. 
//!
//! @remark Some of the methods provided are not thread-safe.
class LuaEngine
{

	//! To store the stack's index.
	//!
	static int mTop;

public:

	//! Reports a scripting error.
	//!
	//! @param err The error message
	static void ReportError(std::string const & err)
	{
		std::cerr << err << std::endl;
	}

	//! Reports errors, if any, by checking the Lua stack.
	//!
	//! @param ls lua_State
	//! @param cod State value. Generally, the value returned by these functions
	//! which may fail.
	static void ReportError(lua_State * ls, int cod)
	{
		if ( cod && lua_gettop(ls) >= 1) 
		{
			std::stringstream ss;
			ss << "[LUA]" << 
				lua_tostring(ls, -1) << std::endl;
			lua_pop(ls, 1);
			std::cerr << ss.str() << std::endl;
		}
	}

	//! Reports errors, if any.
	//!
	//! @param ls lua_State
	//! @param cod State value. Generally, the value returned by these functions
	//! which may fail.
	static void ReportError(lua_State * ls)
	{
		if ( lua_gettop(ls) >= 1) 
		{
			std::stringstream ss;
			ss << "[LUA]" << 
				lua_tostring(ls, -1) << std::endl;
			lua_pop(ls, 1);
			MessageBox(0, ss.str().c_str(), "LUA error", 0);
			std::cerr << ss.str() << std::endl;
		}
	}

	//! Loads and executes a Lua script. Because lua functions within the
	//! script are not executed by themselves (only free code is actually
	//! executed) it may be used simply to load these functions into the
	//! lua state, for them to be called later.
	//!
	//! @param ls Lua state.
	//! @param file Relative or absolute path to the script file to load.
	static void RunFile(lua_State * ls, std::string const & file)
	{
		int ret = 
			luaL_loadfile(ls, file.c_str());
		if(ret==0)
			lua_pcall(ls,0,0,0);
		else
		{
			std::stringstream ss;
			ss << "Could not load LUA file " << file << ": " <<
				lua_tostring(ls, -1) << std::endl;
			throw std::runtime_error(ss.str());
		}
	}

	
	//! This function pushes a pointer to a SWIG-generated type into the Lua stack.
	//! It has been obtained from the SWIG examples.
	//!
	//! @param L lua_State
	//! @param ptr Pointer to push into the Lua stack
	//! @param type_name Name of the pointer's type. It can be found in the files
	//! generated by SWIG. Normally it matches its logical name.
	//! @param owned If true, ownership will be transferred to Lua.
	static void PushPointer(lua_State * L, void* ptr, const char* type_name, 
		int owned = 0) 
	{	
		// Locate the type.
		swig_type_info * pTypeInfo = SWIG_TypeQuery(L, type_name);
		if (pTypeInfo == 0)
			throw std::runtime_error(std::string("Type not found: ") + type_name);  

		// Push the pointer. Specify that ownership will be transferred to Lua.
		SWIG_NewPointerObj(L, ptr, pTypeInfo, owned);
	}

	//! Begins a call to a Lua function. After starting a call, the function parameters
	//! should be pushed into the stack.
	//!
	//! @param L Pointer to the Lua state.
	//! @param name Name of the Lua function to call.
	//!
	//! @remark BeginCall and EndCall are not thread-safe. The user must guarantee
	//! that BeginCall and EndCall pairs are executed atomically.
	static void BeginCall(lua_State * L, std::string const & name) 
	{
		mTop = lua_gettop(L); // Obtain the index of the top of the stack.
		lua_pushstring(L, name.c_str()); // Push the function name.
		lua_gettable(L, LUA_GLOBALSINDEX);
		if (!lua_isfunction(L, -1)) 
		{
			// We couldn't find it or it isn't a function. Fix the stack so that it 
			// recovers its original state and throw an exception.

			lua_settop(L, mTop);
			throw std::runtime_error(
				std::string("LuaEng::BeginCall error. Function could not be found: ") +
				name
				);
		}
	}

	//! It finishes a call. (It carries out the call itself). 
	//! The arguments to pass to the function must have been pushed into the Lua 
	//! stack before calling this method.
	//!
	//! @param L Pointer to the Lua state.
	//! @param numArgs Number of arguments that have been pushed into the stack.
	static void EndCall(lua_State * L, int numArgs)
	{
		if (lua_pcall(L, numArgs, 0, 0) != 0)  // Llama a la funci�n con numArgs argumentos. 
		{
			throw std::runtime_error(lua_tostring(L, -1));
			lua_settop(L, mTop); 
		}
		lua_settop(L, mTop);
	}


}; // !LuaEng


#endif