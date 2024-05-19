
#include <iostream>
#include <stdexcept>

#include "lstate.h"
#include "LuaWrapper.h"
#include "NPCManager.h"
#include "lua.hpp"

int Lua_Test(lua_State*)
{
	std::cout << "Hey there!" << std::endl;
	return 0;
}

int Lua_AddNPC(lua_State* luaStatePtr)
{
	std::cout << lua_tolstring(luaStatePtr, int(1), NULL) << "\n";
	//NPCManager::GetInstance().AddNPC(std::move(name));
	return 0;
}

int Lua_RemoveNPC(lua_State*)
{
	//std::string name{ lua_tostring(luaStatePtr, 1) };
	//NPCManager::GetInstance().RemoveNPC("hey");
	return 0;
}


void LuaStringTest(const LuaWrapper& wrapper)
{
	const std::string luaCode = R"(
            a = 1 + 1;
            print("1+1=" .. a);
			)";
	wrapper.PerformString(luaCode);
}

void LuaFunctionTest(const LuaWrapper& wrapper)
{
	wrapper.Register("hey", Lua_Test);
	const std::string luaCode = R"(
            a = 1 + 1;
            print("1+1=" .. a);
			hey();
			)";
	wrapper.PerformString(luaCode);
}

void LuaFileTest(const LuaWrapper& wrapper)
{
	wrapper.Register("addNPC", Lua_AddNPC);
	wrapper.Register("removeNPC", Lua_RemoveNPC);
	wrapper.PerformFile("luaScripts/startup.lub");
	NPCManager::GetInstance().Dump();
}

int main()
{
	const LuaWrapper wrapper{};

	try
	{
		//LuaStringTest(wrapper);
		//LuaFunctionTest(wrapper);
		LuaFileTest(wrapper);
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << std::endl;
	}
	
	return 0;
}
