#include "ConfigurationManager.h"

#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

ConfigurationManager ConfigurationManager::s_Instance;

ConfigurationManager& ConfigurationManager::GetInstance()
{
	return s_Instance;
}

void ConfigurationManager::Init()
{
	LoadConfiguration();
}

std::unordered_map<BlockName, TextureAtlas> ParseJson(json data) {
	std::unordered_map<BlockName, TextureAtlas> TextureMappings;


	for (auto it = data.begin(); it != data.end(); it++) {
		auto& blockNames = it.value();
		for (auto blockName = blockNames.begin(); blockName != blockNames.end(); blockName++) {
			BlockName nameOfBlock;

			if (blockName.key() == "dirt")
				nameOfBlock = BlockName::Dirt;
			else if (blockName.key() == "cobblestone")
				nameOfBlock = BlockName::Cobblestone;

			auto& compositeSides = blockName.value();

			TextureAtlas textureAtlas;

			for (auto compositeSide = compositeSides.begin(); compositeSide != compositeSides.end(); compositeSide++) {
				auto& edges = compositeSide.value();

				Face tempFace;
				for (auto edge = edges.begin(); edge != edges.end(); edge++) {

					if (edge.key() == "top")
						tempFace.Top = edge.value();
					else if (edge.key() == "bottom")
						tempFace.Bottom = edge.value();
					else if (edge.key() == "left")
						tempFace.Left = edge.value();
					else if (edge.key() == "right")
						tempFace.Right = edge.value();
				}
				if (compositeSide.key() == "top")
					textureAtlas.Top = tempFace;
				else if (compositeSide.key() == "side")
					textureAtlas.Sides = tempFace;
				else if (compositeSide.key() == "base")
					textureAtlas.Base = tempFace;
			}
			TextureMappings[nameOfBlock] = textureAtlas;
		}
	}

	return TextureMappings;
}

TextureAtlas ConfigurationManager::GetTextureAtlas(BlockName name)
{
	return m_BlockTextureMappings[name];
}

void ConfigurationManager::LoadConfiguration()
{
	std::ifstream f("src/AssetManager/texture_mappings.json");
	json data = json::parse(f);

	m_BlockTextureMappings = ParseJson(data);
}
