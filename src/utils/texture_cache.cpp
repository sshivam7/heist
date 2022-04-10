#include "texture_cache.h"

#include "../../lib/stb_image.h"

TextureCache::TextureCache() {

}

TextureCache::~TextureCache() {

}

Texture TextureCache::getTexture(std::string name) {
	return m_textures[name];
}

void TextureCache::loadTexture(std::string name, const char* fileName, bool alpha) {
    Texture texture;
    if (alpha)
    {
        texture.setFormat(GL_RGBA, GL_RGBA);
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(fileName, &width, &height, &nrChannels, 0);

    texture.Generate(width, height, data);
    // free image data
    stbi_image_free(data);
	m_textures[name] = texture;
}

void TextureCache::clear() {
	for (auto t : m_textures) {
		unsigned int id = t.second.getId();
		glDeleteTextures(1, &id);
	}
}