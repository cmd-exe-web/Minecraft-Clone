#pragma once

#include <glad/glad.h>

#include <vector>

#include "Vertex.h"

struct VertexAttribute {
	unsigned int count;
	unsigned int type;
	bool normalized;

	unsigned int GetSizeOfType() const {
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(GLfloat);
		case GL_INT:
			return sizeof(GLint);
		case GL_UNSIGNED_INT:
			return sizeof(GLuint);
		case GL_UNSIGNED_SHORT:
			return sizeof(GLushort);
		default:
			break;
		}
		static_assert("Invalid Type");
		return 0;
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	template<typename T>
	void Push(unsigned int count);

	inline std::vector<VertexAttribute> GetElements() const { return m_Elements; }
	inline const unsigned int GetStride() const { return m_Stride; }
private:
	std::vector<VertexAttribute> m_Elements;
	unsigned int m_Stride;
};
