#include "texture.h"

Texture::Texture(unsigned int width, unsigned int height) :
	m_width(width),
	m_height(height),
	m_internalFormat(GL_RGB),
	m_imageFormat(GL_RGB),
	m_wrapS(GL_REPEAT),
	m_wrapT(GL_REPEAT),
	m_filterMin(GL_LINEAR),
	m_filterMax(GL_LINEAR) {
	glGenTextures(1, &this->m_id);
}

Texture::Texture() :
	m_width(0),
	m_height(0),
	m_internalFormat(GL_RGB),
	m_imageFormat(GL_RGB),
	m_wrapS(GL_REPEAT),
	m_wrapT(GL_REPEAT),
	m_filterMin(GL_LINEAR),
	m_filterMax(GL_LINEAR) {
	glGenTextures(1, &this->m_id);
}


Texture::~Texture() {
	glDeleteTextures(1, &this->m_id);
}

void Texture::generate(unsigned char* data) {
	glBindTexture(GL_TEXTURE_2D, this->m_id);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		this->m_internalFormat,
		this->m_width,
		this->m_height,
		0,
		this->m_imageFormat,
		GL_UNSIGNED_BYTE,
		data
	);

	// set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_filterMax);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const {
	// Bind texture
	glBindTexture(GL_TEXTURE_2D, this->m_id);
}

unsigned int Texture::getId() {
	return m_id;
}

void Texture::setDim(unsigned int width, unsigned int height) {
	this->m_width = width;
	this->m_height = height;
}

void Texture::setFormat(unsigned int internalFormat, unsigned int imgFormat) {
	this->m_internalFormat = internalFormat;
	this->m_imageFormat = imgFormat;
}

void Texture::setWrap(unsigned int wrapS, unsigned int wrapT) {
	this->m_wrapS = wrapS;
	this->m_wrapT = wrapT;
}

void Texture::setFilter(unsigned int filterMin, unsigned int filterMax) {
	this->m_filterMin = filterMin;
	this->m_filterMax = filterMax;
}
