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

enum GameState {
	GAME_ACTIVE,
	GAME_WIN
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

private:
	GameState m_state;
	bool m_keys[1024];
	unsigned int m_width, m_height;
};

#endif