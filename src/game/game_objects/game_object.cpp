#include "game_object.h"

GameObject::GameObject() :
	m_pos(0.0f, 0.0f),
	m_size(1.0f, 1.0f),
	m_color(1.0f),
	m_rotation(0.0f),
	m_sprite(),
	m_isSolid(true) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color) :
	m_pos(pos),
	m_size(size),
	m_color(color),
	m_rotation(0.0f),
	m_sprite(sprite),
	m_isSolid(true) { }

void GameObject::draw(Sprite& renderer) {
	renderer.drawSprite(this->m_sprite, this->m_pos, this->m_size, this->m_rotation, this->m_color);
}

glm::vec2 GameObject::getPos() {
	return this->m_pos;
}

void GameObject::setPos(glm::vec2 pos) {
	this->m_pos = pos;
}

void GameObject::setPosX(float x) {
	this->m_pos.x = x;
}

void GameObject::setPosY(float y) {
	this->m_pos.y = y;
}

glm::vec2 GameObject::getSize() {
	return this->m_size;
}

void GameObject::setRotation(float rotation) {
	this->m_rotation = rotation;
}