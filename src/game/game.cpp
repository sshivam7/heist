#include "game.h"

#include "../utils/resource_manager.h"
#include "../utils/texture.h"
#include "../utils/shader.h"
#include "../utils/sprite.h"

#include <iostream>
#include <filesystem>

Sprite* renderer;

Game::Game(unsigned int width, unsigned int height) :
	m_state(GAME_ACTIVE), m_keys(), m_width(width), m_height(height) {

}

Game::~Game() {

}

void Game::init() {
	Shader shader("src/shaders/sprite.vs", "src/shaders/sprite.fs");
	// configure shaders
	glm::mat4 proj = glm::ortho(0.0f, static_cast<float>(m_width),
		static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);
	shader.activate();
	shader.setInt("image", 0);
	shader.setMat4("projection", proj);
	// set render-specific controls
	renderer = new Sprite(shader);
	// load textures
	ResourceManager::loadTexture("standard_wall", "resources/standard_wall.png", true);

	// Load game level
	this->loadLevels("src/levels");
}


// Load all game levels from directory 
void Game::loadLevels(std::string path) {
	unsigned int curFile = 0;

	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		std::string loc = entry.path().string();
		std::replace(loc.begin(), loc.end(), '\\', '/');
		
		GameLevel lvl;
		lvl.load_level(loc.c_str(), m_width, m_height);
		this->m_levels.push_back(lvl);

		unsigned int indexOfLastSlash = loc.find_last_of("/");
		std::string fileName = loc.substr(indexOfLastSlash + 1);

		if (fileName == "default.hlvl") {
			this->m_currentLevel = curFile;
		}

		curFile++;
	}
}

void Game::update(float dt) {

}

void Game::processInput(float dt) {

}

void Game::render() {
	if (true) {
		this->m_levels[this->m_currentLevel].draw_walls(*renderer);
	}
}

bool Game::get_key(unsigned int index) {
	return this->m_keys[index];
}

void Game::set_key(unsigned int index, bool new_val) {
	this->m_keys[index] = new_val;
}