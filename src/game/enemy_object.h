/**
* enemy_object.h
* Description: Enemy object. extends game object
* @author Shivam Sood
* @version 1.0
*/

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <unordered_map>

#include "player_object.h"
#include "../utils/texture.h"
#include "path_finding/path_map.h"

class EnemyObject : public PlayerObject {
public:
	EnemyObject();
	EnemyObject(glm::vec2 pos, glm::vec2 size, float velocity, Texture sprite);

	std::vector<glm::vec2> findPath(
		PathMap& pathMap,
		glm::vec2 dest,
		unsigned int screenWidth,
		unsigned int screenHeight
	);

	void move(float dt, glm::vec2 destination);
};

#endif