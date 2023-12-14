#include "CubeRenderer.h"

#include "Graphics/Shapes/Cube.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include "Graphics/VertexBufferLayout.h"
#include "Graphics/IndexBuffer.h"

const int MAX_CUBE_COUNT = 1000;
const int MAX_QUAD_COUNT = MAX_CUBE_COUNT * 6;
const int MAX_VERTEX_COUNT = MAX_QUAD_COUNT * 4;
const int MAX_INDEX_COUNT = MAX_QUAD_COUNT * 6;

struct RenderData
{
	VertexArray* CubeVAO = nullptr;
	VertexBuffer* CubeVBO = nullptr;
	IndexBuffer* CubeIBO = nullptr;

	Vertex* QuadBuffer = nullptr;
	Vertex* QuadOffsetPtr = nullptr;


	uint32_t* QuadIndexBuffer = nullptr;
	uint32_t* QuadIndexOffsetPtr = nullptr;

	uint32_t IndexCount = 0;
	uint32_t VertexCount = 0;

	CubeRenderer::Stats RenderStats;
};

static RenderData s_Data;

void CubeRenderer::Init()
{
	s_Data.QuadBuffer = new Vertex[MAX_VERTEX_COUNT];
	s_Data.QuadIndexBuffer = new uint32_t[MAX_INDEX_COUNT];

	s_Data.CubeVAO = new VertexArray;
	s_Data.CubeVAO->Bind();

	s_Data.CubeVBO = new VertexBuffer(MAX_VERTEX_COUNT * sizeof(Vertex));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	s_Data.CubeVAO->AddBuffers(*s_Data.CubeVBO, layout);

	s_Data.CubeIBO = new IndexBuffer(MAX_INDEX_COUNT);
	s_Data.CubeVAO->Unbind();
	s_Data.CubeVBO->Unbind();
	s_Data.CubeIBO->Unbind();
}

void CubeRenderer::Shutdown()
{
}

void CubeRenderer::BeginBatch()
{
	s_Data.QuadOffsetPtr = s_Data.QuadBuffer;
	s_Data.QuadIndexOffsetPtr = s_Data.QuadIndexBuffer;
	s_Data.IndexCount = 0;
	s_Data.VertexCount = 0;
}

void CubeRenderer::EndBatch()
{
	s_Data.CubeVBO->UploadData(s_Data.QuadBuffer, s_Data.VertexCount * sizeof(Vertex));
	s_Data.CubeIBO->UploadData(s_Data.QuadIndexBuffer, s_Data.IndexCount);

}

void CubeRenderer::Flush()
{
	s_Data.CubeVAO->Bind();
	s_Data.CubeIBO->Bind();
	glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, 0);
	s_Data.RenderStats.DrawCount++;
}

const CubeRenderer::Stats& CubeRenderer::GetStats()
{
	return s_Data.RenderStats;
}

void CubeRenderer::ResetStats()
{
	s_Data.RenderStats.CubeCount = 0;
	s_Data.RenderStats.DrawCount = 0;
}

void CubeRenderer::DrawCube(CubeBuilder cubeBuilder, glm::vec3 position)
{
	if( s_Data.VertexCount + 24 >= MAX_VERTEX_COUNT ||
		s_Data.IndexCount + 36 >= MAX_INDEX_COUNT)
	{
		EndBatch();
		Flush();
		BeginBatch();
	}
	Cube::GenerateVertices(s_Data.QuadOffsetPtr, position, cubeBuilder);
	s_Data.IndexCount += Cube::GenerateIndices(s_Data.QuadIndexOffsetPtr, cubeBuilder, s_Data.VertexCount);
	s_Data.VertexCount += 4 * 6;
	s_Data.RenderStats.CubeCount++;
}
