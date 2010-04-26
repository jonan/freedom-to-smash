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


#include "luautils.hpp"
#include "lua_engine.hpp"

#include <string>

Ogre::Vector3 lua_vectorexpr( lua_State * L, const char * expr, Ogre::Vector3 const & def )
{
    std::string exprbuf = "evalExpr=";
    exprbuf += expr;

    if( !luaL_dostring(L, exprbuf.c_str()) )
    {
        lua_getglobal( L, "evalExpr" );

        swig_type_info * pTypeInfo = SWIG_TypeQuery(L, "Ogre::Vector3 *");
        if (pTypeInfo == 0)
            throw std::runtime_error(std::string(
            "Could not find vector type."));

        void * vvect = 0;
        SWIG_Lua_ConvertPtr(L, -1, &vvect, pTypeInfo, 0);
        if(vvect)
        {
            Ogre::Vector3 * vectp = (Ogre::Vector3*)vvect;
            return *vectp;
        }
    }

    return def;
}
