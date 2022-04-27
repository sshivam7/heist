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
	Shader();
	Shader(const char* vertexShaderFile, const char* fragmentShaderFile);
	~Shader();

	// Member functions
	void activate();
	unsigned int getId();

	void setInt(const char* name, int val);
	void setVec3(const char* name, const glm::vec3& vec);
	void setMat4(const char* name, const glm::mat4& matrix);

private:
	// Reference to shader program ID
	unsigned int m_id;
	// private helper functions
	void checkErrors(unsigned int shader, const char* type);
};

#endif