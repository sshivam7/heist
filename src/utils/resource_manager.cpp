#include "resource_manager.h"

TextureCache ResourceManager::s_textureCache;

Texture ResourceManager::getTexture(std::string name) {
	return s_textureCache.getTexture(name);
}

void ResourceManager::loadTexture(std::string name, const char* fileName, bool alpha) {
	s_textureCache.loadTexture(name, fileName, alpha);
}

void ResourceManager::clear() {
	s_textureCache.clear();
}