#include "texture_cache.h"

TextureCache::TextureCache() {

}

TextureCache::~TextureCache() {

}

Texture TextureCache::getTexture(std::string name) {
	return m_textures[name];
}

void TextureCache::loadTexture(std::string name, const char* fileName, bool alpha) {
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);

	Texture texture(width, height);

	if (alpha) {
		texture.setFormat(GL_RGBA, GL_RGBA);
	}

	texture.generate(data);
	
	//free image data
	stbi_image_free(data);
	m_textures[name] = texture;
}

void TextureCache::clear() {
	for (auto t : m_textures) {
		unsigned int id = t.second.getId();
		glDeleteTextures(1, &id);
	}
}