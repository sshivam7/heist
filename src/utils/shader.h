/**
* shader.h
* Description: OpenGl Shader Class
* @author Shivam Sood
* @version 1.0
*/

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

class Shader {
public:
	// Constructors & Destructor
	Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
	~Shader();

	// Member functions
	void activate();

private:
	// Reference to shader program ID
	unsigned int m_id;
	// private helper functions
	void checkErrors(unsigned int shader, const char* type);
};

#endif