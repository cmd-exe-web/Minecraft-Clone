#include "Mesh.h"

#include "VertexBufferLayout.h"

Mesh::Mesh(Cube& cube)
	:cube(cube)
{
	m_VAO = new VertexArray;
	m_VAO->Bind();
	m_VBO = new VertexBuffer(cube.GetVertices(), cube.GetBufferSize());
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO->AddBuffers(*m_VBO, layout);

	m_IBO = new IndexBuffer(cube.GetIndices(), cube.GetIndexCount());
	m_VAO->Unbind();
	m_VBO->Unbind();
	m_IBO->Unbind();

}

Mesh::~Mesh()
{
}

void Mesh::Render()
{
	m_VAO->Bind();
	m_IBO->Bind();
	glDrawElements(GL_TRIANGLES, cube.GetIndexCount(), GL_UNSIGNED_INT, 0);
	m_VAO->Unbind();
}
