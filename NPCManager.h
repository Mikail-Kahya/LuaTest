#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>

class NPC
{
	std::string m_name;
	int m_health{};
public:
	explicit NPC(std::string name) : m_name(std::move(name)) {}
	const std::string& get_name() const { return m_name; }
	int get_health() const { return m_health; }
	void set_health(int health) { m_health = health; }
};

class NPCManager
{
	std::vector<NPC> m_npcs;
public:
	static NPCManager& GetInstance()
	{
		static NPCManager instance{};
		return instance;
	}

	void AddNPC(const std::string&& name)
	{
		m_npcs.emplace_back(NPC(name));
	}

	void RemoveNPC(const std::string& name)
	{
		m_npcs.erase(std::remove_if(m_npcs.begin(), m_npcs.end(),
			[name](NPC& npc) {return npc.get_name() == name; }), m_npcs.end());
	}

	void SetHealth(const std::string& name, int health)
	{
		auto foundNPC = std::find_if(m_npcs.begin(), m_npcs.end(), [&name](const NPC& npc)
			{
				return npc.get_name() == name;
			});

		if (foundNPC != m_npcs.end())
			foundNPC->set_health(health);
	}

	void Dump() const
	{
		std::cout << "Available NPC's:" << std::endl;
		for (const auto& npc : m_npcs)
		{
			std::cout << "NPC " << npc.get_name() << std::endl;
			std::cout << "\tHealth: " << npc.get_health() << std::endl;
		}
			
		std::cout << "NPC count:" << m_npcs.size() << std::endl;
	}
};