
#include <iostream>
#include <stdexcept>

#include "LuaWrapper.h"

int Lua_CppFunction(lua_State*)
{
	std::cout << "This c++ function was called in lua!" << std::endl;
	return 0;
}

int main()
{
	const LuaWrapper wrapper{};

	try
	{
		wrapper.Register("hey", Lua_CppFunction);
		const std::string luaCode = R"(
            a = 1 + 1
            print("1+1=" .. a)
			hey();
			)";
		wrapper.PerformString(luaCode);
		
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << std::endl;
	}
	
	return 0;
}
