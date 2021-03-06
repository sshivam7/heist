/**
* player_object.h
* Description: Player object. Extends game object 
* @author Shivam Sood
* @version 1.0
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"

class PlayerObject : public GameObject {
public:
	// Constructors
	PlayerObject();
	PlayerObject(glm::vec2 pos, glm::vec2 size, float velocity, Texture sprite);

	// Getter & Setter methods
	void setVelocity(float v);
	float getVelocity();
	float getRadius();

private:
	// Member variables
	float m_velocity;
	float m_radius;
};

#endif