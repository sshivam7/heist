#include "util.h"

// Read from file and store data in string 
std::string readFile(const char* fileName) {
	std::string shaderCode;

	try {
		std::ifstream codeFile(fileName);
		if (!codeFile) {
			std::cout << "ERROR::FILE: Could not be opened" << std::endl;
		}
		std::stringstream shaderStream;
		shaderStream << codeFile.rdbuf();

		codeFile.close();
		shaderCode = shaderStream.str();
	}
	catch (std::exception e) {
		std::cerr << "ERROR:FILE: Failed to read file " << std::endl;
	}

	return shaderCode;
}

glm::vec3 getFloatCol(unsigned int r, unsigned int g, unsigned int b) {
	return glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f);
}