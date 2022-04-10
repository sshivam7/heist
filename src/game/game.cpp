#include "game.h"

#include "../utils/resource_manager.h"
#include "../utils/texture.h"
#include "../utils/shader.h"
#include "../utils/sprite.h"

#include <iostream>

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
	ResourceManager::loadTexture("face", "resources/awesomeface.png", true);
}

void Game::update(float dt) {

}

void Game::processInput(float dt) {

}

void Game::render() {
	Texture spriteTexture = ResourceManager::getTexture("face");
	renderer->DrawSprite(spriteTexture,
		glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f),
		45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

bool Game::get_key(unsigned int index) {
	return this->m_keys[index];
}

void Game::set_key(unsigned int index, bool new_val) {
	this->m_keys[index] = new_val;
}