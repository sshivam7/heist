#include "game.h"

#include "../utils/resource_manager.h"
#include "../utils/texture.h"
#include "../utils/shader.h"
#include "../utils/sprite.h"
#include "path_finding/path_map.h"
#include "path_finding/path_finding.h"

#include <iostream>
#include <filesystem>

Sprite* renderer;
PlayerObject* player;
std::vector<EnemyObject> enemies;
std::vector<GameObject> coins;

std::vector<int> path_indicies;
std::vector<std::vector<glm::vec2>> paths;

PathMap pathMap;

typedef std::tuple<bool, Direction> CollisionInfo;

CollisionInfo checkCollision(glm::vec2 pos, float radius, GameObject& two);
bool rectCollision(GameObject& one, GameObject& two);
Direction getCollisionDirection(glm::vec2 target);

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
	coins = this->m_levels[this->m_currentLevel].getCoins();
	pathMap = this->m_levels[this->m_currentLevel].getPathMap();

	// Initialize Enemy path finding data
	for (int i = 0; i < enemies.size(); ++i) {
		paths.push_back(enemies[i].findPath(pathMap, player->getPos(), m_width, m_height));
		path_indicies.push_back(0);
	}
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

float timerCurrent = 0.0;
float timerTotal = 1.0;

void Game::update(float dt) {
	if (this->m_state == GAME_ACTIVE) {
		timerCurrent += dt;
		if (timerCurrent >= timerTotal) {
			for (int i = 0; i < enemies.size(); ++i) {
				paths[i] = enemies[i].findPath(pathMap, player->getPos(), m_width, m_height);
				path_indicies[i] = 1;
			}
			timerCurrent -= timerTotal;
		}

		for (int i = 0; i < enemies.size(); ++i) {
			updateEnemies(dt, enemies[i], paths[i], path_indicies[i]);
			
			if (checkEnemyCollision(enemies[i], *player)) {
				this->m_state = GAME_LOSE;
			}
		}

		// Remove coins if collision with player
		std::vector<GameObject>::iterator iter;
		for (iter = coins.begin(); iter != coins.end(); ) {
			if (rectCollision(*iter, *player)) {
				iter = coins.erase(iter);
			}
			else {
				++iter;
			}
		}

		if (coins.empty()) {
			this->m_state = GAME_WIN;
		}
	}
}

void Game::updateEnemies(float dt, EnemyObject& enemy, std::vector<glm::vec2>& path, int& path_index) {
	if (path_index < path.size() && !path.empty()) {

		if (enemy.getPos() != path[path_index]) {
			enemy.move(dt, path[path_index]);
		}

		if (std::abs(enemy.getPos().y - path[path_index].y) < 1 &&
			std::abs(enemy.getPos().x - path[path_index].x) < 1) {
			path_index++;
		}
	}
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

		for (GameObject& coin : coins) {
			coin.draw(*renderer);
		}
	}
}

bool Game::get_key(unsigned int index) {
	return this->m_keys[index];
}

void Game::set_key(unsigned int index, bool new_val) {
	this->m_keys[index] = new_val;
}

Direction Game::checkPlayerCollisions(glm::vec2 pos, float radius) {
	// Get all objects located in the current grid based on player position
	std::vector<std::vector<GameObject>> grids = m_levels[m_currentLevel].getWalls().getGridSet(pos);
	Direction colDir = NONE;

	// Check for collisions with player object
	for (std::vector<GameObject> grid : grids) {
		for (GameObject& wall : grid) {
			CollisionInfo collision = checkCollision(pos, radius, wall);
			if (std::get<0>(collision)) {
				// std::cout << "COLLISION: " << std::get<1>(collision) << std::endl;
				colDir = std::get<1>(collision);
			}
		}
	}
	
	return colDir;
}

bool Game::checkEnemyCollision(EnemyObject& one, GameObject& two) {
	return std::get<1>(checkCollision(one.getPos(), one.getRadius(), two));
}

bool rectCollision(GameObject& one, GameObject& two) {
	bool xCollision = one.getPos().x + one.getSize().x >= two.getPos().x &&
		two.getPos().x + two.getSize().x >= one.getPos().x;

	bool yCollision = one.getPos().y + one.getSize().y >= two.getPos().y &&
		two.getPos().y + two.getSize().y >= one.getPos().y;

	return xCollision && yCollision;
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
