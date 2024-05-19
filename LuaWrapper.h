#pragma once
#include <string>

struct lua_State;

class LuaWrapper final
{
public:
	LuaWrapper();
	~LuaWrapper();

	void PerformString(const std::string& expression) const;
	void Register(const std::string& name, int func(lua_State*)) const;
	void PerformFile(const std::string& filePath) const;
private:
	lua_State* m_LuaState{};
};
