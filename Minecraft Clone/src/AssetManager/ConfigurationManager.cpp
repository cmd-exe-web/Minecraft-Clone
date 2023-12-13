#include "ConfigurationManager.h"

#include <iostream>
#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

ConfigurationManager ConfigurationManager::s_Instance;

ConfigurationManager& ConfigurationManager::GetInstance()
{
	return s_Instance;
}


TextureAtlas ConfigurationManager::GetTexCoords(BlockName name)
{
	return TextureAtlas();
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

			std::cout << blockName.key() << "::" << std::endl;

			TextureAtlas textureAtlas;

			for (auto compositeSide = compositeSides.begin(); compositeSide != compositeSides.end(); compositeSide++) {
				auto& edges = compositeSide.value();

				std::cout << compositeSide.key() << ":-" << std::endl;

				Face tempFace;
				for (auto edge = edges.begin(); edge != edges.end(); edge++) {

					if (edge.key() == "top")
						tempFace.Top = edge.value();
					if (edge.key() == "bottom")
						tempFace.Bottom = edge.value();
					if (edge.key() == "left")
						tempFace.Left = edge.value();
					if (edge.key() == "right")
						tempFace.Right = edge.value();

					std::cout << edge.key() << " : " << edge.value() << std::endl;
				}
				std::cout << std::endl;

				if (compositeSide.key() == "top")
					textureAtlas.Top = tempFace;
				if (compositeSide.key() == "side")
					textureAtlas.Sides = tempFace;
				if (compositeSide.key() == "base")
					textureAtlas.Base = tempFace;
			}

			TextureMappings[nameOfBlock] = textureAtlas;
		}
	}

	return TextureMappings;
}

void ConfigurationManager::LoadConfiguration()
{
	std::ifstream f("src/AssetManager/texture_mappings.json");
	json data = json::parse(f);

	m_BlockTextureMappings = ParseJson(data);
}
