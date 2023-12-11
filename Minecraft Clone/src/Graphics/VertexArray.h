#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;
	void AddLayout(const VertexBufferLayout& layout) const;
	void AddBuffers(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
	unsigned int m_Id;
};
