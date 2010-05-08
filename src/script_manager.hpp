/*
This file is part of Freedom to Smash.
Copyright (C) 2009-2010 FTS Team

Freedom to Smash is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

/// @file
/// Script manager class.
/// @author LRG

#ifndef SCRIPT_MANAGER_HPP
#define SCRIPT_MANAGER_HPP



extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class ScriptManager
{

	static ScriptManager * mInstance;

	lua_State * mL;

	ScriptManager()
		: mL(0)
	{
	}

public:

	//! Returns the Lua state.
	//!
	lua_State * getL() 
	{
		return mL;
	}

	//! Returns a reference to the script manager instance.
	//!
	ScriptManager & get()
	{
		if(!mInstance)
			mInstance = new ScriptManager();
		return *mInstance;
	}

	//! Destroys the script manager, if it has been instanced.
	//!
	void destroy()
	{
		delete mInstance;
		mInstance = 0;
	}

};



#endif // SCRIPT_MANAGER_HPP
