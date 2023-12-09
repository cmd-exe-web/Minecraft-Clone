#pragma once

#include "glm/glm.hpp"

#include "Builder/CubeBuilder.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
};

/*

			7- - - - - - - -6
		   /|			   /|
		  /	|			  /	|				Y
		 3 - - - - - - - 2	|				|
		 |	|			 |	|				|
		 |	|	  .		 |	|				|_______X
		 |	|		     |	|			   /
		 |	4- - - - - - |-	5			  /
		 | / 		     | /			 Z
		 |/	 		     |/	 
		 0- - - - - - - -1
*/
class Cube
{
public:
	Cube(CubeBuilder& cubeBuilder);
	~Cube();

	inline Vertex* GetVertices() { return m_Vertices; }
	inline unsigned int* GetIndices() { return m_Indices; }
	inline unsigned int GetBufferSize() { return m_BufferSize; }
	inline unsigned int GetIndexCount() { return m_IndexCount; }
private:
	Vertex m_Vertices[24] = {
		// Front Face
		{ { -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f } },		// 0   
		{ {  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f } },		// 1
		{ {  0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f } },		// 2
		{ { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f } },		// 3       
		// Back Face
		{ { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f } },		// 4
		{ {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f } },		// 5
		{ {  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f } },		// 6
		{ { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f } },		// 7
		// Left Face
		{ { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f } },		// 4  ->  8           
		{ { -0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f } },		// 0  ->  9  
		{ { -0.5f,  0.5f,  0.5f }, { 1.0f, 1.0f } },		// 3  ->  10      
		{ { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f } },		// 7  ->  11
		// Right Face
		{ {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f } },		// 1  ->  12
		{ {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f } },		// 5  ->  13
		{ {  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f } },		// 6  ->  14
		{ {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f } },		// 2  ->  15
		// Top Face
		{ { -0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f } },		// 3  ->  16      
		{ {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f } },		// 2  ->  17
		{ {  0.5f,  0.5f, -0.5f }, { 1.0f, 1.0f } },		// 6  ->  18
		{ { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f } },		// 7  ->  19
		// Bottom Face
		{ { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f } },		// 4  ->  20
		{ {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f } },		// 5  ->  21
		{ {  0.5f, -0.5f,  0.5f }, { 1.0f, 1.0f } },		// 1  ->  22
		{ { -0.5f, -0.5f,  0.5f }, { 0.0f, 1.0f } },		// 0  ->  23  
	};
	unsigned int* m_Indices;
	unsigned int m_BufferSize;
	unsigned int m_IndexCount;
};

