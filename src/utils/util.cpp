#include "util.h"

// Read from file and store data in string 
std::string readFile(const char* fileName) {
	std::ifstream input(fileName);
	if (!input.is_open()) {
		std::cerr << "ERROR::FILE >> " << fileName
			<< " failed to open" << std::endl;
	}
	return std::string((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
}