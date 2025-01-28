#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>

Texture::Texture()
	:mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{

}

Texture::~Texture()
{

}

bool Texture::Load(const std::string& fileName)
{
    int channels = 0;
    unsigned char* image = stbi_load(fileName.c_str(), &mWidth, &mHeight, &channels, 0);

    if (image == nullptr)
    {
        return false;
    }

    int format = GL_RGB;
    if (channels == 4)
    {
        format = GL_RGBA;
    }
    else if (channels == 1)
    {
        format = GL_RED;
    }

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return true;
}

void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}