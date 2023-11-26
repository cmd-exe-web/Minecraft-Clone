#include "VertexArray.h"

#include "glad/glad.h"

VertexArray::VertexArray()
	:m_Id(0)
{
	glGenVertexArrays(1, &m_Id);
}

VertexArray::~VertexArray()
{
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_Id);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffers(const VertexBuffer& vb, const VertexBufferLayout& layout) 
{
	Bind();
	vb.Bind();
	
	const std::vector<VertexAttribute> layoutElements = layout.GetElements();

	int offset = 0;
	for (int i = 0; i < layoutElements.size() ; i++) {
		const auto& element = layoutElements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * element.GetSizeOfType();
	}

}
