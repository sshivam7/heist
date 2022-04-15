#include "player.h"

PlayerObject::PlayerObject() :
	GameObject(), m_velocity(500.0f) {
	m_radius = this->getSize().x / 2;
}

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, float velocity, Texture sprite) :
	GameObject(pos, size, sprite, glm::vec3(1.0f)), m_velocity(velocity) {
	m_radius = this->getSize().x / 2;
}

void PlayerObject::setVelocity(float v) {
	this->m_velocity = v;
}

float PlayerObject::getVelocity() {
	return this->m_velocity;
}

float PlayerObject::getRadius() {
	return this->m_radius;
}