#include "enemy_object.h"
#include <queue>

#include <iostream>

EnemyObject::EnemyObject() :
	PlayerObject() {
}

EnemyObject::EnemyObject(glm::vec2 pos, glm::vec2 size, float velocity, Texture sprite) :
PlayerObject(pos, size, velocity, sprite) {

}

namespace std {
	/* implement hash function so we can put GridLocation into an unordered_set */
	template <> struct hash<glm::vec2> {
		std::size_t operator()(const glm::vec2& id) const noexcept {
			// NOTE: better to use something like boost hash_combine
			return std::hash<int>()((int)id.x ^ ((int)id.y << 16));
		}
	};
}

std::unordered_map<glm::vec2, glm::vec2> EnemyObject::findPath(
	PathMap pathMap,
	glm::vec2 dest,
	unsigned int wallWidth, 
	unsigned int wallheight
) {
	std::queue<Tile> frontier;
	Tile startPos = pathMap.getByArrLoc(this->getPos().x / wallWidth, this->getPos().y / wallheight);
	frontier.push(startPos);
	
	std::unordered_map<glm::vec2, glm::vec2> came_from;
	came_from[startPos.getPos()] = startPos.getPos();

	while (!frontier.empty()) {
		Tile current = frontier.front();
		frontier.pop();

		// std::cout << "Current: " << current.getPos().x / wallWidth << ", " << current.getPos().y / wallheight << std::endl;
		if (current.getPos() == dest) {
			break;
		}

		for (Tile next : pathMap.getNeighbours(current)) {
			if (came_from.find(next.getPos()) == came_from.end()) {
				std::cout << "T: " << next.getPos().x / wallWidth << ", " << next.getPos().y / wallheight << std::endl;
				frontier.push(next);
				came_from[next.getPos()] == current.getPos();
			}
		}
	}
	return came_from;
}

// Move object in given direction
void EnemyObject::move(float dt, glm::vec2 direction) {
	this->setPos(this->getPos() + direction * (this->getVelocity() * dt));
}
