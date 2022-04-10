#include "game_level.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "../utils/util.h"

GameLevel::GameLevel() {

}

void GameLevel::load_level(const char* fileName, unsigned int width, unsigned int height) {
	// Clear old wall data
	this->m_walls.clear();

	GameLevel level;
	std::string line;
	std::ifstream fstream(fileName);
	std::vector<std::vector<unsigned int>> mapData;

	unsigned int tileVal;

	if (fstream) {
		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileVal) {
				row.push_back(tileVal);
			}
			mapData.push_back(row);
		}
		if (mapData.size() > 0) {
			this->init(mapData, width, height);
		}
	}
}

void GameLevel::draw_walls(Sprite& renderer) {
	for (GameObject& wall : this->m_walls) {
		wall.draw(renderer);
	}
}

void GameLevel::init(std::vector<std::vector<unsigned int>> mapData, unsigned int levelWidth, unsigned int levelHeight) {
	// Calculate wall height 
	unsigned int arr_width = mapData[0].size();
	unsigned int arr_height = mapData.size();
	float wall_width = levelWidth / static_cast<float>(arr_width);
	float wall_height = levelHeight / arr_height;

	for (int col = 0; col < arr_height; ++col) {
		for (int row = 0; row < arr_width; ++row) {
			if (mapData[col][row] == 1) {
				glm::vec2 pos(wall_width * row, wall_height * col);
				glm::vec2 size(wall_width, wall_height);
				GameObject obj(pos, size, ResourceManager::getTexture("standard_wall"), getFloatCol(48, 165, 191));
				this->m_walls.push_back(obj);
			}
		}
	}
}