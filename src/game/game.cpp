#include "game.h"

#include "../utils/resource_manager.h"
#include "../utils/texture.h"
#include "../utils/shader.h"
#include "../utils/sprite.h"
#include "player.h"

#include <iostream>
#include <filesystem>

Sprite* renderer;
PlayerObject* player;
std::vector<EnemyObject> enemies;

typedef std::tuple<bool, Direction> CollisionInfo;

Game::Game(unsigned int width, unsigned int height) :
	m_state(GAME_ACTIVE), m_keys(), m_width(width), m_height(height) { }

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
	ResourceManager::loadTexture("brick_wall", "resources/brick_wall.png", true);
	ResourceManager::loadTexture("player", "resources/player.png", true);
	ResourceManager::loadTexture("enemy", "resources/enemy.png", true);
	ResourceManager::loadTexture("coin", "resources/coin.png", true);

	// Load game level
	this->loadLevels("src/levels");
	player = this->m_levels[this->m_currentLevel].getPlayer();
	enemies = this->m_levels[this->m_currentLevel].getEnemies();
}


// Load all game levels from directory 
void Game::loadLevels(std::string path) {
	unsigned int curFile = 0;

	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		std::string loc = entry.path().string();
		std::replace(loc.begin(), loc.end(), '\\', '/');
		
		GameLevel lvl(m_width, m_height);
		lvl.loadLevel(loc.c_str(), m_width, m_height);
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
	if (this->m_state == GAME_ACTIVE) {
		float velocity = player->getVelocity() * dt;
		float radius = player->getRadius();
		glm::vec2 pos = player->getPos();
		glm::vec2 size = player->getSize();

		if (this->m_keys[GLFW_KEY_A]) {
			glm::vec2 lPos(pos.x - velocity, pos.y);
			if (pos.x >= 0.0f && checkPlayerCollisions(lPos, radius) != LEFT) {
				player->setPosX(pos.x -= velocity);
			}
			player->setRotation(270.0f);
		}
		else if (this->m_keys[GLFW_KEY_D]) {
			glm::vec2 rPos(pos.x + velocity, pos.y);
			if (pos.x <= m_width - size.x && checkPlayerCollisions(rPos, radius) != RIGHT) {
				player->setPosX(pos.x += velocity);
			}
			player->setRotation(90.0f);
		}
		else if (this->m_keys[GLFW_KEY_W]) {
			glm::vec2 uPos(pos.x, pos.y - velocity);
			if (pos.y >= 0.0f && checkPlayerCollisions(uPos, radius) != UP) {
				player->setPosY(pos.y -= velocity);
			}
			player->setRotation(0.0f);
		}
		else if (this->m_keys[GLFW_KEY_S]) {
			glm::vec2 dPos(pos.x, pos.y + velocity);
			if (pos.y <= m_height - size.y && checkPlayerCollisions(dPos, radius) != DOWN) {
				player->setPosY(pos.y += velocity);
			}
			player->setRotation(180.0f);
		}
	}
}

void Game::render() {
	if (this->m_state == GAME_ACTIVE) {
		this->m_levels[this->m_currentLevel].drawWalls(*renderer);
		player->draw(*renderer);

		for (EnemyObject& enemy : enemies) {
			enemy.draw(*renderer);
		}
	}
}

bool Game::get_key(unsigned int index) {
	return this->m_keys[index];
}

void Game::set_key(unsigned int index, bool new_val) {
	this->m_keys[index] = new_val;
}


CollisionInfo checkCollision(PlayerObject& one, GameObject& two);
CollisionInfo checkCollision(glm::vec2 pos, float radius, GameObject& two);
Direction getCollisionDirection(glm::vec2 target);

Direction Game::checkPlayerCollisions(glm::vec2 pos, float radius) {
	// Get all objects located in the current grid based on player position
	std::vector<std::vector<GameObject>> grids = m_levels[m_currentLevel].getWalls().getGridSet(pos);
	Direction colDir = NONE;

	// Check for collisions with player object
	for (std::vector<GameObject> grid : grids) {
		for (GameObject& wall : grid) {
			CollisionInfo collision = checkCollision(pos, radius, wall);
			if (std::get<0>(collision)) {
				std::cout << "COLLISION" << std::get<1>(collision) << std::endl;
				colDir = std::get<1>(collision);
			}
		}
	}
	
	return colDir;
}

CollisionInfo checkCollision(PlayerObject& one, GameObject& two) {
	// Get circle center
	glm::vec2 center(one.getPos() + one.getRadius());
	
	// Calculate AABB center & half-extents
	glm::vec2 halfExtents(two.getSize().x / 2.0f, two.getSize().y / 2.0f);
	glm::vec2 boxCenter(two.getPos().x + halfExtents.x, two.getPos().y + halfExtents.y);

	// get difference vector between centers
	glm::vec2 difference = center - boxCenter;
	glm::vec2 clamped = glm::clamp(difference, -halfExtents, halfExtents);
	glm::vec2 closest = boxCenter + clamped;

	// Vector between circle center and closest point on box
	difference = closest - center;

	if (glm::length(difference) <= one.getRadius()) {
		return std::make_tuple(true, getCollisionDirection(difference));
	}
	else {
		return std::make_tuple(false, UP);
	}
}

CollisionInfo checkCollision(glm::vec2 pos, float radius, GameObject& two) {
	// Get circle center
	glm::vec2 center(pos + radius);

	// Calculate AABB center & half-extents
	glm::vec2 halfExtents(two.getSize().x / 2.0f, two.getSize().y / 2.0f);
	glm::vec2 boxCenter(two.getPos().x + halfExtents.x, two.getPos().y + halfExtents.y);

	// get difference vector between centers
	glm::vec2 difference = center - boxCenter;
	glm::vec2 clamped = glm::clamp(difference, -halfExtents, halfExtents);
	glm::vec2 closest = boxCenter + clamped;

	// Vector between circle center and closest point on box
	difference = closest - center;

	if (glm::length(difference) <= radius) {
		return std::make_tuple(true, getCollisionDirection(difference));
	}
	else {
		return std::make_tuple(false, UP);
	}
}

Direction getCollisionDirection(glm::vec2 target) {
	glm::vec2 compass[] = {
		glm::vec2(0.0f, -1.0f), // DOWN
		glm::vec2(0.0f, 1.0f),  // UP
		glm::vec2(-1.0f, 0.0f), // LEFT
		glm::vec2(1.0f, 0.0f)   // RIGHT
	};

	float max = 0.0f;
	unsigned int bestMatch = -1;
	for (unsigned int i = 0; i < 4; ++i) {
		float dotProd = glm::dot(glm::normalize(target), compass[i]);
		if (dotProd > max) {
			max = dotProd;
			bestMatch = i;
		}
	}

	return (Direction)bestMatch;
}
