/**
* texture.h
* Description: OpenGl Texture Class
* @author Shivam Sood
* @version 1.0
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture {
public:
	// Construct & Destructor
	Texture(unsigned int width, unsigned int height);
	~Texture();

	void generate(const char* data);
	void bind() const;
	void configure(
		unsigned int internalFormat,
		unsigned int imgFormat,
		unsigned int wrapS,
		unsigned int wrapT,
		unsigned int filterMin,
		unsigned int filterMax
	);

private:
	unsigned int m_id;
	// Image dimensions
	unsigned int m_width, m_height;
	// Texture formating & configuration
	unsigned int m_internalFormat, m_imageFormat;
	unsigned int m_wrapS, m_wrapT;
	unsigned int m_filterMin, m_filterMax;
};


#endif