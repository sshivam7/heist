#include "shader.h"

#include <iostream>
#include <fstream>
#include <streambuf>

#include "util.h"

// Shader constructor
Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile) {
	const char* vertexShaderSource = readFile(vertexShaderFile).c_str();
	const char* fragmentShaderSource = readFile(fragmentShaderFile).c_str();

	// Create, attach, & compile vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkErrors(vertexShader, "VERTEX");

	// Create, attach, & compile fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkErrors(fragmentShader, "FRAGMENT");

	// Create shader program & attach vertex and fragment shaders
	this->m_id = glCreateProgram();
	glAttachShader(this->m_id, vertexShader);
	glAttachShader(this->m_id, fragmentShader);

	// Link shaders into shader program
	glLinkProgram(this->m_id);
	checkErrors(m_id, "PROGRAM");

	// Delete unnecessary shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(this->m_id);
}

void Shader::activate() {
	glUseProgram(this->m_id);
}

unsigned int Shader::getId() {
	return this->m_id;
}

void Shader::setVec3(const char* name, const glm::vec3& vec) {
	unsigned int loc = glGetUniformLocation(this->m_id, name);
	glUniform3f(loc, vec.x, vec.y, vec.z);
}

void Shader::setMat4(const char* name, const glm::mat4& matrix) {
	unsigned int loc = glGetUniformLocation(this->m_id, name);
	glUniformMatrix4fv(loc, 1, false, glm::value_ptr(matrix));
}

void Shader::checkErrors(unsigned int shader, const char* type) {
	GLint success;
	char infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR:SHADER >> Compile Error for " << type << "\n"
				<< infoLog << "\n\n" << std::endl;
		}
	}
	else {
		glGetShaderiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR:SHADER >> LINK Error for " << type << "\n"
				<< infoLog << "\n\n" << std::endl;
		}
	}
}