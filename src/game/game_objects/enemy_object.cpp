#include "enemy_object.h"

#include <queue>
#include <iostream>

#include "../path_finding/path_finding.h"

EnemyObject::EnemyObject() :
	PlayerObject() {}

EnemyObject::EnemyObject(glm::vec2 pos, glm::vec2 size, float velocity, Texture sprite) :
PlayerObject(pos, size, velocity, sprite) {}

// Find path to destination from current enemy location
std::vector<glm::vec2> EnemyObject::findPath(
	PathMap& pathMap,
	glm::vec2 dest,
	unsigned int screenWidth,
	unsigned int screenHeight
) {
	float tileWidth = (screenWidth / static_cast<float>(pathMap.getColSize()));
	float tileHeight = (screenHeight / static_cast<float>(pathMap.getRowSize()));
	
	std::vector<glm::vec2> path;
	Tile startTile = pathMap.getByArrLoc(
		(int)(this->getPos().y / tileHeight),
		(int)(this->getPos().x / tileWidth)
	);
	Tile endTile = pathMap.getByArrLoc(dest.y / tileHeight, dest.x / tileWidth);
	aStarPathFind(pathMap, startTile, endTile, path);

	return path;
}

// Move object in given direction
void EnemyObject::move(float dt, glm::vec2 destination) {
	glm::vec2 direction = glm::normalize(destination - this->getPos());
	direction.x = (int)std::round(direction.x);
	direction.y = (int)std::round(direction.y);

	if (direction == glm::vec2(0, 1)) {
		this->setRotation(180);
	}
	else if (direction == glm::vec2(0, -1)) {
		this->setRotation(0);
	}
	else if (direction == glm::vec2(1, 0)) {
		this->setRotation(90);
	}
	else if (direction == glm::vec2(-1, 0)) {
		this->setRotation(270);
	}

	this->setPos(this->getPos() + direction * (this->getVelocity() * dt));
}
