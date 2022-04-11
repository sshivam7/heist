#include "game_level.h"

#include <fstream>
#include <sstream>
#include <iostream>

#include "../utils/util.h"
#include "../utils/texture.h"

GameLevel::GameLevel() {

}

void GameLevel::loadLevel(const char* fileName, unsigned int width, unsigned int height) {
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

void GameLevel::drawWalls(Sprite& renderer) {
	for (GameObject& wall : this->m_walls) {
		wall.draw(renderer);
	}
}

PlayerObject* GameLevel::getPlayer() {
	return &this->m_player;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> mapData, unsigned int levelWidth, unsigned int levelHeight) {
	// Calculate wall height 
	unsigned int arr_width = mapData[0].size();
	unsigned int arr_height = mapData.size();
	float wall_width = levelWidth / static_cast<float>(arr_width);
	float wall_height = levelHeight / arr_height;

	for (int col = 0; col < arr_height; ++col) {
		for (int row = 0; row < arr_width; ++row) {
			glm::vec2 pos(wall_width * row, wall_height * col);
			glm::vec2 size(wall_width, wall_height);

			// Draw all fixed map objects 
			if (mapData[col][row] > 0 && mapData[col][row] <= 2) {
				Texture texture;
				glm::vec3 color;
				switch (mapData[col][row]) {
				case 1:
					color = getFloatCol(142, 191, 36);
					texture = ResourceManager::getTexture("standard_wall");
					break;
				case 2:
					color = getFloatCol(191, 148, 96);
					texture = ResourceManager::getTexture("brick_wall");
					break;
				}
				GameObject obj(pos, size, texture, color);
				this->m_walls.push_back(obj);
			}
			else if (mapData[col][row] == 9) {
				PlayerObject obj(pos, size, 125.0f, ResourceManager::getTexture("player"));
				this->m_player = obj;
			}
		}
	}
}