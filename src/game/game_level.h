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

#include "./game_objects/game_object.h"
#include "./game_objects/enemy_object.h"
#include "./game_objects/player_object.h"
#include "path_finding/path_map.h"
#include "../utils/sprite.h"
#include "../utils/resource_manager.h"
#include "../utils/level_grid.h"

class GameLevel {
public:
	GameLevel(unsigned int width, unsigned int height);

	void loadLevel(const char* fileName, unsigned int width, unsigned int height);
	void drawWalls(Sprite& renderer);

	PlayerObject* getPlayer();
	LevelGrid<GameObject> getWalls();
	std::vector<EnemyObject> getEnemies();
	std::vector<GameObject> getCoins();

	PathMap getPathMap();

private:
	unsigned int m_width, m_height;
	// Walls
	LevelGrid<GameObject> m_walls;
	PlayerObject m_player;
	std::vector<EnemyObject> m_enemies;
	std::vector<GameObject> m_coins;
	PathMap m_pathMap;

	// Initialize data
	void init(std::vector<std::vector<unsigned int>> mapData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif