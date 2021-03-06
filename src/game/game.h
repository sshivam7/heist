/**
* game.h
* Description: Game logic for Heist
* @author Shivam Sood
* @version 1.0
*/

#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "game_level.h"
#include "collision_detection.h"

enum GameState {
	GAME_ACTIVE,
	GAME_WIN,
	GAME_LOSE,
	MAIN_MENU
};

// Holds all game data and functionality
class Game {
public:
	// Constructors & Destructor 
	Game(unsigned int width, unsigned int height);
	~Game();

	// Member functions
	void init();
	void processInput(float dt);
	void update(float dt);
	void render();

	bool get_key(unsigned int index);
	void set_key(unsigned int index, bool new_val);
	void setProcessedKey(unsigned int index, bool new_val);

private:
	GameState m_state;
	std::vector<GameLevel> m_levels;
	unsigned int m_currentLevel;
	unsigned int m_totalLevels;

	bool m_keys[1024];
	bool m_keysProcessed[1024];
	unsigned int m_width, m_height;

	// Helper functions
	void loadLevels(std::string path);
	void loadEntities();
	void updateEnemies(float dt, EnemyObject& enemy, std::vector<glm::vec2>& path, int& path_index);
	Direction checkPlayerCollisions(glm::vec2 pos, float radius);
	bool checkEnemyCollision(EnemyObject& one, GameObject& two);
};

#endif