/**
* util.h
* Description: Utility functions used in Heist game
* @author Shivam Sood
* @version 1.0
*/

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

std::string readFile(const char* fileName);
glm::vec3 getFloatCol(unsigned int r, unsigned int g, unsigned int b);

#endif