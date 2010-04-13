 //Archivo: luautils.cpp
 //
 //Creditos: Este archivo ha sido creado por Andrew Lim
 //http://windrealm.com/tutorials/reading-a-lua-configuration-file-from-c.php#downloads


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