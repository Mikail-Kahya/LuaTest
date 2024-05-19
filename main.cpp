
#include <iostream>
#include <stdexcept>

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
	if (!lua_isstring(luaStatePtr, 1))
		return 0;

	NPCManager::GetInstance().AddNPC(lua_tostring(luaStatePtr, 1));
	return 0;
}

int Lua_RemoveNPC(lua_State* luaStatePtr)
{
	if (!lua_isstring(luaStatePtr, 1))
		return 0;

	NPCManager::GetInstance().RemoveNPC(lua_tostring(luaStatePtr, 1));
	return 0;
}

int Lua_SetNPCHealth(lua_State* luaStatePtr)
{
	constexpr int32_t nrDataMembers{ 2 };
	constexpr int32_t luaIdx{ -1 };
	int32_t health{};
	std::string name{};
	

	for (int idx{}; idx < nrDataMembers; ++idx)
	{
		bool isString{ static_cast<bool>(lua_isstring(luaStatePtr, luaIdx)) };
		bool isInt{ static_cast<bool>(lua_isinteger(luaStatePtr, luaIdx)) };

		if (isInt)
			health = static_cast<int32_t>(lua_tointeger(luaStatePtr, luaIdx));
		else if (isString)
			name = lua_tostring(luaStatePtr, luaIdx);
		else
			return 0;
		lua_pop(luaStatePtr, 1);
	}

	if (name.empty())
		return 0;

	NPCManager::GetInstance().SetHealth(name, health);

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

void LuaOwnFileTest(const LuaWrapper& wrapper)
{
	wrapper.Register("addNPC", Lua_AddNPC);
	wrapper.Register("removeNPC", Lua_RemoveNPC);
	wrapper.Register("setNPCHealth", Lua_SetNPCHealth);
	wrapper.PerformFile("luaScripts/test.lua");
	NPCManager::GetInstance().Dump();
}

int main()
{
	const LuaWrapper wrapper{};

	try
	{
		//LuaStringTest(wrapper);
		//LuaFunctionTest(wrapper);
		//LuaFileTest(wrapper);
		LuaOwnFileTest(wrapper);
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << std::endl;
	}
	
	return 0;
}
