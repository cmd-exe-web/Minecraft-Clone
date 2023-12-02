#include "Texture.h"

#include <iostream>

#include "stb_image/stb_image.h"

Texture::Texture(GLenum textureTarget, const char* filePath, Format format)
	:m_TextureTarget(textureTarget), m_FilePath(filePath), m_Format(format), m_Id(0), m_Height(0), m_Width(0), m_BPP(0), m_LocalBuffer(nullptr)
{
}

Texture::~Texture()
{
}

void Texture::Load()
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(m_FilePath, &m_Width, &m_Height, &m_BPP, 0);

	if (!m_LocalBuffer) {
		std::cerr << "Can't load texture from " << m_FilePath << " - " << stbi_failure_reason();
	}

	GLenum format;
	GLint internalFormat;

	if (m_Format == Format::PNG) {
		format = GL_RGBA;
		internalFormat = GL_RGBA;
	}
	else if(m_Format == Format::JPG) {
		format = GL_RGB;
		internalFormat = GL_RGB;
	}

	glGenTextures(1, &m_Id);
	glBindTexture(m_TextureTarget, m_Id);
	if (m_TextureTarget == GL_TEXTURE_2D) {
		glTexImage2D(m_TextureTarget, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer);
	}
	else {
		std::cerr << "Support for texture target is not implemented" << std::endl;
		exit(1);
	}
	glTexParameteri(m_TextureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(m_TextureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_TextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(m_TextureTarget, 0);

	stbi_image_free(m_LocalBuffer);
}

void Texture::Bind(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(m_TextureTarget, m_Id);

}

void Texture::Unbind()
{
}
