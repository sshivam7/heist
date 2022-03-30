/**
*	game.h
*	Description: Game logic for Heist
*	@author Shivam Sood
*	@version 1.0
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
	GameState state;
	bool keys[1024];
	unsigned int width, height;

	// Constructors & Destructor 
	Game(unsigned int width, unsigned int height);
	~Game();

	// Member functions
	void init();
	void processInput(float dt);
	void update(float dt);
	void render();
};

#endif