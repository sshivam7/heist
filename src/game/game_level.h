/**
* game_level.h
* Description: Class to define & render game level (loads map from file)
* @author Shivam Sood
* @version 1.0
*/


#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "../utils/sprite.h"
#include "../utils/resource_manager.h"

class GameLevel {
public:
	GameLevel();

	void load_level(const char* fileName, unsigned int width, unsigned int height);
	void draw_walls(Sprite& renderer);

private:
	// Walls
	std::vector<GameObject> m_walls;

	// Initialize data
	void init(std::vector<std::vector<unsigned int>> mapData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif