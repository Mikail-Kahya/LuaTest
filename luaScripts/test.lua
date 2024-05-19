
npcs = {}

npcs[1] = { name = 'Rob jobs', health = 5 }
npcs[2] = { name = 'hey I am test', health = 2 }
npcs[3] = { name = 'You c# without classes', health = 5 }
npcs[4] = { name = 'Hold your horses!', health = 4 }
	
for key, value in ipairs(npcs) do
	addNPC(value.name)
	setNPCHealth(value.name, value.health)
end