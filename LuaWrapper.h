#pragma once
#include <string>

struct lua_State;

class LuaWrapper final
{
public:
	LuaWrapper();
	~LuaWrapper();

	void PerformString(const std::string& expression) const;

private:
	lua_State* m_LuaState{};
};
