/*
This file is part of Freedom to Smash.
Copyright (C) 2009 Jon Ander Peñalba <jonan88@gmail.com>

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

#include "script.hpp"

#include <cstdlib>

#include <lua.hpp>

#include "input.hpp"

// Constructor
Script::Script(void)
{
    lua = lua_open();
    luaL_openlibs(lua);
}

// Destructor
Script::~Script(void)
{
    lua_close(lua);
}

// Loads an runs a given script.
void Script::loadScript(std::string file_name)
{
    std::string full_name = "scripts/" + file_name;
    if (luaL_loadfile(lua, full_name.c_str()) || lua_pcall(lua, 0, 0, 0))
        exit(EXIT_FAILURE);
}

// Defines variables to be used in the script.
void Script::defineGlobalVariable(double var, const char *name)
{
    lua_pushnumber(lua, var);
    lua_setglobal(lua, name);
}

// Defines variables to be used in the script.
void Script::defineGlobalVariable(const char *var, const char *name)
{
    lua_pushstring(lua, var);
    lua_setglobal(lua, name);
}

// Gets the value of a given variable.
void Script::getGlobalVariable(const char *name, double &var)
{
    lua_getglobal(lua, name);
    var = lua_tonumber(lua, -1);
    lua_remove(lua, -1);
}

// Gets the value of a given variable.
void Script::getGlobalVariable(const char *name, int &var)
{
    lua_getglobal(lua, name);
    var = static_cast<int>(lua_tonumber(lua, -1));
    lua_remove(lua, -1);
}
