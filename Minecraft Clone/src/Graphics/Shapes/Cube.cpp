#include "Cube.h"

#include <cassert>

#include "AssetManager/ConfigurationManager.h"

/*

			7- - - - - - - -6
		   /|			   /|
		  /	|			  /	|				Y
		 3 - - - - - - - 2	|				|
		 |	|			 |	|				|
		 |	|			 |	|				|_______X
		 |	|		     |	|			   /
		 |	4- - - - - - |-	5			  /
		 | / 		     | /			 Z
		 |/	 		     |/	 
		 0- - - - - - - -1
*/
// Left
// 4  ->  8 
// 0  ->  9 
// 3  ->  10
// 7  ->  11
// Right 
// 1  ->  12
// 5  ->  13
// 6  ->  14
// 2  ->  15
// Top 
// 3  ->  16
// 2  ->  17
// 6  ->  18
// 7  ->  19
// Bottom 
// 4  ->  20
// 5  ->  21
// 1  ->  22
// 0  ->  23

void Cube::GenerateVertices(Vertex*& vertices, glm::vec3 position, const CubeBuilder& cubeBuilder)
{
	auto textureAtlas = cubeBuilder.Name;
	*vertices = { { position.x + -0.5f, position.y + -0.5f, position.z +  0.5f }, { 0.0f, 0.0f } };		// 0   
	vertices++;
	*vertices = { { position.x +  0.5f, position.y + -0.5f, position.z +  0.5f }, { 1.0f, 0.0f } };		// 1
	vertices++;
	*vertices = { { position.x +  0.5f, position.y +  0.5f, position.z +  0.5f }, { 1.0f, 1.0f } };		// 2
	vertices++;
	*vertices = { { position.x + -0.5f, position.y +  0.5f, position.z +  0.5f }, { 0.0f, 1.0f } };		// 3       
	vertices++;

	*vertices = { { position.x + -0.5f, position.y + -0.5f, position.z + -0.5f }, { 0.0f, 0.0f } };		// 4
	vertices++;
	*vertices = { { position.x +  0.5f, position.y + -0.5f, position.z + -0.5f }, { 1.0f, 0.0f } };		// 5
	vertices++;
	*vertices = { { position.x +  0.5f, position.y +  0.5f, position.z + -0.5f }, { 1.0f, 1.0f } };		// 6
	vertices++;
	*vertices = { { position.x + -0.5f, position.y +  0.5f, position.z + -0.5f }, { 0.0f, 1.0f } };		// 7
	vertices++;

	*vertices = { { position.x + -0.5f, position.y + -0.5f, position.z + -0.5f }, { 0.0f, 0.0f } };		// 4  ->  8           
	vertices++;
	*vertices = { { position.x + -0.5f, position.y + -0.5f, position.z +  0.5f }, { 1.0f, 0.0f } };		// 0  ->  9  
	vertices++;
	*vertices = { { position.x + -0.5f, position.y +  0.5f, position.z +  0.5f }, { 1.0f, 1.0f } };		// 3  ->  10      
	vertices++;
	*vertices = { { position.x + -0.5f, position.y +  0.5f, position.z + -0.5f }, { 0.0f, 1.0f } };		// 7  ->  11
	vertices++;

	*vertices = { { position.x +  0.5f, position.y + -0.5f, position.z +  0.5f }, { 0.0f, 0.0f } };		// 1  ->  12
	vertices++;
	*vertices = { { position.x +  0.5f, position.y + -0.5f, position.z + -0.5f }, { 1.0f, 0.0f } };		// 5  ->  13
	vertices++;
	*vertices = { { position.x +  0.5f, position.y +  0.5f, position.z + -0.5f }, { 1.0f, 1.0f } };		// 6  ->  14
	vertices++;
	*vertices = { { position.x +  0.5f, position.y +  0.5f, position.z +  0.5f }, { 0.0f, 1.0f } };		// 2  ->  15
	vertices++;

	*vertices = { { position.x + -0.5f, position.y +  0.5f, position.z +  0.5f }, { 0.0f, 0.0f } };		// 3  ->  16      
	vertices++;
	*vertices = { { position.x +  0.5f, position.y +  0.5f, position.z +  0.5f }, { 1.0f, 0.0f } };		// 2  ->  17
	vertices++;
	*vertices = { { position.x +  0.5f, position.y +  0.5f, position.z + -0.5f }, { 1.0f, 1.0f } };		// 6  ->  18
	vertices++;
	*vertices = { { position.x + -0.5f, position.y +  0.5f, position.z + -0.5f }, { 0.0f, 1.0f } };		// 7  ->  19
	vertices++;

	*vertices = { { position.x + -0.5f, position.y + -0.5f, position.z + -0.5f }, { 0.0f, 0.0f } };		// 4  ->  20
	vertices++;
	*vertices = { { position.x +  0.5f, position.y + -0.5f, position.z + -0.5f }, { 1.0f, 0.0f } };		// 5  ->  21
	vertices++;
	*vertices = { { position.x +  0.5f, position.y + -0.5f, position.z +  0.5f }, { 1.0f, 1.0f } };		// 1  ->  22
	vertices++;
	*vertices = { { position.x + -0.5f, position.y + -0.5f, position.z +  0.5f }, { 0.0f, 1.0f } };		// 0  ->  23  
	vertices++;


}

uint32_t Cube::GenerateIndices(uint32_t*& indices, CubeBuilder& cubeBuilder, uint32_t vertexCount)
{
	unsigned short numFaces = 0;
	for (int i = 0; i < 6; i++) {
		if (cubeBuilder.VisibleFaces[i]) 
			numFaces++;
	}

	unsigned int numIndices = numFaces * 6;

	int offset = 0;
	if (cubeBuilder.VisibleFaces[(int)Direction::Front]) {
		indices[offset++] = vertexCount + 0;
		indices[offset++] = vertexCount + 1;
		indices[offset++] = vertexCount + 2;
		indices[offset++] = vertexCount + 2;
		indices[offset++] = vertexCount + 3;
		indices[offset++] = vertexCount + 0;
	}
	if (cubeBuilder.VisibleFaces[(int)Direction::Back]) {
		indices[offset++] = vertexCount + 5;
		indices[offset++] = vertexCount + 4;
		indices[offset++] = vertexCount + 7;
		indices[offset++] = vertexCount + 7;
		indices[offset++] = vertexCount + 6;
		indices[offset++] = vertexCount + 5;
	}																	 
	if (cubeBuilder.VisibleFaces[(int)Direction::Left]) {                
		indices[offset++] = vertexCount + 8;                                         
		indices[offset++] = vertexCount + 9;                                         
		indices[offset++] = vertexCount + 10;                                         
		indices[offset++] = vertexCount + 10;                                         
		indices[offset++] = vertexCount + 11;                                         
		indices[offset++] = vertexCount + 8;                                         
	}                                                                    
	if (cubeBuilder.VisibleFaces[(int)Direction::Right]) {               
		indices[offset++] = vertexCount + 12;                                         
		indices[offset++] = vertexCount + 13;                                         
		indices[offset++] = vertexCount + 14;                                         
		indices[offset++] = vertexCount + 14;                                         
		indices[offset++] = vertexCount + 15;                                         
		indices[offset++] = vertexCount + 12;                                         
	}                                                                    
	if (cubeBuilder.VisibleFaces[(int)Direction::Top]) {                 
		indices[offset++] = vertexCount + 16;                                         
		indices[offset++] = vertexCount + 17;                                         
		indices[offset++] = vertexCount + 18;
		indices[offset++] = vertexCount + 18;
		indices[offset++] = vertexCount + 19;
		indices[offset++] = vertexCount + 16;
	}
	if (cubeBuilder.VisibleFaces[(int)Direction::Bottom]) {
		indices[offset++] = vertexCount + 20;
		indices[offset++] = vertexCount + 21;
		indices[offset++] = vertexCount + 22;
		indices[offset++] = vertexCount + 22;
		indices[offset++] = vertexCount + 23;
		indices[offset++] = vertexCount + 20;
	}

	// Advancing the offset pointer to the correction position 
	indices += numIndices;

	assert(offset == numIndices);
	return numIndices;
}


Cube::~Cube()
{
}

