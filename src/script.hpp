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

/// @file
/// The Script class.
/// @author Jonan

#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <string>

#include "macros.hpp"

// Lua classes
class lua_State;

/// Class to work with Lua scripts.
class Script {
public:
    Script(void); // Constructor
    ~Script(void); // Destructor

    /// Loads an runs a given script.
    /// @param[in] file_name The script's name.
    void loadScript(std::string file_name);

    // @{
    /// Defines variables to be used in the script.
    /// Must be called before loadScript().
    /// @param[in] var The variable's value.
    /// @param[in] name The variable's name.
    void defineGlobalVariable (double      var, const char *name);
    void defineGlobalVariable (const char *var, const char *name);
    // @}

    // @}
    /// Gets the value of a given variable.
    /// Must be called after loadScript().
    /// @param[in] name The variable's name.
    /// @param[out] var The variable's value.
    void getGlobalVariable (const char *name, double &var);
    void getGlobalVariable (const char *name, int    &var);
    // @}

private:
    lua_State *lua;

    DISALLOW_COPY_AND_ASSIGN(Script);
};

#endif // SCRIPT_HPP
