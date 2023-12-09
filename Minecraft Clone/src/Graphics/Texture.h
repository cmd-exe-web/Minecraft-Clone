#pragma once

#include <glad/glad.h>

enum class Format {
	PNG, JPG
};

class Texture {
public:
	Texture(GLenum textureTarget, const char* filePath, Format format);
	~Texture();

	void Load();
	void Bind(GLenum textureUnit);
	void Unbind();
private:
	GLuint m_Id;
	GLenum m_TextureTarget;
	Format m_Format;
	const char* m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Height, m_Width, m_BPP;
};
