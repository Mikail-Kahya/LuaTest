#include "LuaWrapper.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include "lua.hpp"


LuaWrapper::LuaWrapper()
	: m_LuaState{ luaL_newstate() }
{
	assert(m_LuaState != nullptr);
	luaL_openlibs(m_LuaState);
}

LuaWrapper::~LuaWrapper()
{
	lua_close(m_LuaState);
}

void LuaWrapper::PerformString(const std::string& expression) const
{
	if (luaL_dostring(m_LuaState, expression.c_str()) != LUA_OK)
		throw std::runtime_error("No string could be performed");
}

void LuaWrapper::Register(const std::string& name, int func(lua_State*)) const
{
	lua_register(m_LuaState, name.c_str(), func);
}

void LuaWrapper::PerformFile(const std::string& filePath) const
{
	if (luaL_dofile(m_LuaState, filePath.c_str()) != LUA_OK)
		throw std::runtime_error("No file could be performed");

}
