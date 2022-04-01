/**
* resource_manager.h
* Description: Class to manage game resources
* @author Shivam Sood
* @version 1.0
*/

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <glad/glad.h>

#include "texture_cache.h"
#include "texture.h"

class ResourceManager {
public:
	// Texture Cache wrappers
	static Texture getTexture(std::string name);
	static void loadTexture(std::string name, const char* fileName, bool alpha);
	static void clear();

private:
	static TextureCache s_textureCache;
};

#endif