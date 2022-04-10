/**
* sprite.h
* Description: Class for rendering sprites (modified from https://learnopengl.com/)
* @version 1.0
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class Sprite {
public:
	// Constructor & Destructor
	Sprite(Shader& shader);
	~Sprite();

	// Renders a defined quad textured with given sprite
	void drawSprite(
		Texture& texture,
		glm::vec2 position,
		glm::vec2 size = glm::vec2(10.0f, 10.0f),
		float rotate = 0.0f,
		glm::vec3 color = glm::vec3(1.0f)
	);

private:
	Shader m_shader;
	unsigned int m_quadVAO;

	void initRenderData();
};

#endif