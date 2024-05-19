#include "LuaWrapper.h"

#include <cassert>
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