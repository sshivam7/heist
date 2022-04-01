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
	// Constructs & Destructor
	Texture(unsigned int width, unsigned int height);
	Texture();
	~Texture();

	void generate(unsigned char* data);
	void bind() const;

	// Configuration methods
	void setDim(unsigned int width, unsigned int height);
	void setFormat(unsigned int interalFormat, unsigned int imgFormat);
	void setWrap(unsigned int wrapS, unsigned int wrapT);
	void setFilter(unsigned int filterMin, unsigned int filterMax);

	// Getters
	unsigned int getId();

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