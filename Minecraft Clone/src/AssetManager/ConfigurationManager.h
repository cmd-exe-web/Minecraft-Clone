#pragma once

#include <unordered_map>

#include "BlockType.h"

class ConfigurationManager
{
public:
	static ConfigurationManager& GetInstance();
	void Init();

	ConfigurationManager(const ConfigurationManager&) = delete;
	void operator=(ConfigurationManager&) = delete;

	TextureAtlas GetTextureAtlas(BlockName name);
private:
	ConfigurationManager() {
	}
	void LoadConfiguration();
private:
	std::unordered_map<BlockName, TextureAtlas> m_BlockTextureMappings;
	static ConfigurationManager s_Instance;
};
