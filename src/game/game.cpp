#include "game.h"

Game::Game(unsigned int width, unsigned int height) :
	m_state(GAME_ACTIVE), m_keys(), m_width(width), m_height(height) {

}

Game::~Game() {

}

void Game::init() {

}

void Game::update(float dt) {

}

void Game::processInput(float dt) {

}

void Game::render() {

}

bool Game::get_key(unsigned int index) {
	return this->m_keys[index];
}

void Game::set_key(unsigned int index, bool new_val) {
	this->m_keys[index] = new_val;
}