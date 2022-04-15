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

#include "player.h"
#include "../utils/texture.h"

class EnemyObject : public PlayerObject {
public:
	EnemyObject();
	EnemyObject(glm::vec2 pos, glm::vec2 size, float velocity, Texture sprite);
};

#endif