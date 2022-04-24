/**
* game_object.h
* Description: Base game object class
* @author Shivam Sood
* @version 1.0
*/

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../utils/texture.h"
#include "../utils/sprite.h"

class GameObject {
public:
	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color = glm::vec3(1.0f));
	
	// drawing sprite
	virtual void draw(Sprite& renderer);

	// Getters & setters
	glm::vec2 getPos();
	void setPos(glm::vec2 pos);
	void setPosX(float x);
	void setPosY(float y);
	
	glm::vec2 getSize();
	void setRotation(float rotation);

private:
	glm::vec2 m_pos, m_size;
	glm::vec3 m_color;
	float m_rotation;

	bool m_isSolid;
	Texture m_sprite;
};

#endif