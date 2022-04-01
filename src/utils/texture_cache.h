#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <map>
#include <string>

/**
* texture_cache.h
* Description: Texture Cache to store textures
* @author Shivam Sood
* @version 1.0
*/

#include "texture.h"

#include "../../lib/stb_image.h"

class TextureCache {
public:
	// Constructor & Destructor
	TextureCache();
	~TextureCache();

	// Accessors for textures
	Texture getTexture(std::string name);
	void loadTexture(std::string name, const char* fileName, bool alpha);
	void clear();

private:
	std::map<std::string, Texture> m_textures;
};

#endif