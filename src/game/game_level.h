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
#include "player.h"
#include "../utils/sprite.h"
#include "../utils/resource_manager.h"

class GameLevel {
public:
	GameLevel();

	void loadLevel(const char* fileName, unsigned int width, unsigned int height);
	void drawWalls(Sprite& renderer);

	PlayerObject* getPlayer();
	void getWalls();

private:
	// Walls
	std::vector<GameObject> m_walls;
	PlayerObject m_player;

	// Initialize data
	void init(std::vector<std::vector<unsigned int>> mapData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif