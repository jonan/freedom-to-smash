
#ifndef _LUAEVAL_HPP
#define _LUAEVAL_HPP

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
class LuaEval
{
	lua_State * L;
	
public:

	LuaEval(lua_State * L)
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
	}

	//! Evaluates an expression and stores the result in a double.
	//! If an error occurs, false is returned and the double is not modified.
	//!
	//! @param expr Lua expression to evaluate to a double.
	//! @param number Double which will keep the result.
	//! @return True on success, false on error. 
	bool evalNumber(std::string const & expr, double & number)
	{
	}

	//! Evaluates an expression and stores the result in a string.
	//! If an error occurs, false is returned and the string is not modified.
	//!
	//! @param expr Lua expression to evaluate to a string.
	//! @param str String which will keep the result.
	//! @return True on success, false on error. 
	bool evalString(std::string const & expr, std::string & str)
	{
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
	}

};



#endif