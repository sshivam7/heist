/**
* player.h
* Description: Player object. extends game object 
* @author Shivam Sood
* @version 1.0
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "../utils/texture.h"

class PlayerObject : public GameObject {
public:
	PlayerObject();
	PlayerObject(glm::vec2 pos, glm::vec2 size, float velocity, Texture sprite);

	void setVelocity(float v);
	float getVelocity();

private:
	float m_velocity;
};

#endif