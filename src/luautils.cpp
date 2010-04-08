 //Archivo: luautils.cpp
 //
 //Creditos: Este archivo ha sido creado por Andrew Lim
 //http://windrealm.com/tutorials/reading-a-lua-configuration-file-from-c.php#downloads


#include "luautils.h"
#include "LuaEng.h"

#include <string>

const char* lua_stringexpr( lua_State* L, const char* expr,
						   const char* def ) {
							   const char* r = def ;
							   char buf[256] = "" ;
							   /* Assign the Lua expression to a Lua global variable. */
							   sprintf( buf, "evalExpr=%s", expr );
							   if ( !luaL_dostring( L, buf ) ) {
								   /* Get the value of the global varibable */
								   lua_getglobal( L, "evalExpr" );
								   if ( lua_isstring( L, -1 ) ) {
									   r = lua_tostring( L, -1 );
								   }
								   /* remove lua_getglobal value */
								   lua_pop( L, 1 );
							   }
							   return r ;
}

int lua_numberexpr( lua_State* L, const char* expr, double* out ) {
	int ok = 0 ;
	char buf[256] = "" ;
	/* Assign the Lua expression to a Lua global variable. */
	sprintf( buf, "evalExpr=%s", expr );
	if ( !luaL_dostring( L, buf ) ) {
		/* Get the value of the global varibable */
		lua_getglobal( L, "evalExpr" );
		if ( lua_isnumber( L, -1 ) ) {
			*out = lua_tonumber( L, -1 );
			ok = 1;
		}
		/* remove lua_getglobal value */
		lua_pop( L, 1 );
	}
	return ok ;
}

int lua_intexpr( lua_State* L, const char* expr, int* out ) {
	double d ;
	int ok = lua_numberexpr( L, expr, &d );
	if ( ok ) {
		*out = (int) d ;
	}
	return ok ;
}

int lua_boolexpr( lua_State* L, const char* expr ) {
	int ok = 0 ;
	char buf[256] = "" ;
	/* Assign the Lua expression to a Lua global variable. */
	sprintf( buf, "evalExpr=%s", expr );
	if ( !luaL_dostring( L, buf ) ) {
		/* Get the value of the global varibable */
		lua_getglobal( L, "evalExpr" );
		if ( lua_isboolean( L, -1 ) ) {
			ok = lua_toboolean( L, -1 );
		}
		/* remove lua_getglobal value */
		lua_pop( L, 1 );
	}
	return ok ;
}

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