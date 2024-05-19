
#include <iostream>
#include <stdexcept>

#include "LuaWrapper.h"

int main()
{
	const LuaWrapper wrapper{};

	try
	{
		const std::string luaCode = R"(
            a = 1 + 1
            print("1+1=" .. a)
			)";
		wrapper.PerformString(luaCode);
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << std::endl;
	}
	
	return 0;
}
