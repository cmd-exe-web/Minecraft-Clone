#pragma once

#include <unordered_map>

#include "BlockType.h"

class ConfigurationManager
{
public:
	static ConfigurationManager& GetInstance();

	ConfigurationManager(const ConfigurationManager&) = delete;
	void operator=(ConfigurationManager&) = delete;

	TextureAtlas GetTexCoords(BlockName name);
private:
	ConfigurationManager() {
		LoadConfiguration();
	}
	void LoadConfiguration();
private:
	std::unordered_map<BlockName, TextureAtlas> m_BlockTextureMappings;
	static ConfigurationManager s_Instance;
};
