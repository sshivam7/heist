/**
* collision_detection.h
* Description: Holds functions implementing collision detection
* @author Shivam Sood
* @version 1.0
*/

#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <tuple>

#include "game_objects/game_object.h"

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

typedef std::tuple<bool, Direction> CollisionInfo;

CollisionInfo checkCollision(glm::vec2 pos, float radius, GameObject& two);
bool rectCollision(GameObject& one, GameObject& two);
Direction getCollisionDirection(glm::vec2 target);

#endif