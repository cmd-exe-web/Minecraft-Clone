#include "VertexBufferLayout.h"

#include <glad/glad.h>

#include <iostream>

VertexBufferLayout::VertexBufferLayout()
	:m_Stride(0), m_Elements()
{
}

VertexBufferLayout::~VertexBufferLayout()
{
}

template<typename T>
void VertexBufferLayout::Push(unsigned int count)
{
	std::cerr << "Invalid type pushed to the layout" << std::endl;
}

template<>
void VertexBufferLayout::Push<float>(unsigned int count) {
	VertexAttribute temp = { count, GL_FLOAT, GL_FALSE };
	m_Elements.push_back(temp);
	m_Stride += count * sizeof(float);
}

template<>
void VertexBufferLayout::Push<int>(unsigned int count) {
	m_Elements.push_back({ count, GL_INT, GL_FALSE });
	m_Stride += count * sizeof(int);
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
	m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
	m_Stride += count * sizeof(unsigned int);
}

template<>
void VertexBufferLayout::Push<unsigned short>(unsigned int count) {
	m_Elements.push_back({ count, GL_UNSIGNED_SHORT, GL_FALSE });
	m_Stride += count * sizeof(unsigned short);
}
