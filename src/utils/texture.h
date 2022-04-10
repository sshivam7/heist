/**
* texture.h
* Description: Class for loading and generating textures (modified from https://learnopengl.com/)
* @version 1.0
*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>


class Texture
{
public:
    // constructor (sets default texture modes)
    Texture();
    // generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
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
    unsigned int m_width, m_height;

    // Texture & image formats
    unsigned int m_internalFormat, m_imageFormat;

    // Wrapping and filtering modes
    unsigned int m_wrapS, m_wrapT;
    unsigned int m_filterMin, m_filterMax;
};

#endif