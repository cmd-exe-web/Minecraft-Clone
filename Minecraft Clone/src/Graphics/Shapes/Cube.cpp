#include "Cube.h"

#include <cassert>

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

Cube::Cube(CubeBuilder& cubeBuilder)
{
	unsigned short numFaces = 0;
	for (int i = 0; i < 6; i++) {
		if (cubeBuilder.VisibleFaces[i]) 
			numFaces++;
	}

	unsigned int numIndices = numFaces * 6;
	m_Indices = new unsigned int[numIndices];

	int offset = 0;
	if (cubeBuilder.VisibleFaces[(int)Direction::Front]) {
		m_Indices[offset++] = 0;
		m_Indices[offset++] = 1;
		m_Indices[offset++] = 2;
		m_Indices[offset++] = 2;
		m_Indices[offset++] = 3;
		m_Indices[offset++] = 0;
	}
	if (cubeBuilder.VisibleFaces[(int)Direction::Back]) {
		m_Indices[offset++] = 5;
		m_Indices[offset++] = 4;
		m_Indices[offset++] = 7;
		m_Indices[offset++] = 7;
		m_Indices[offset++] = 6;
		m_Indices[offset++] = 5;
	}																	 
	if (cubeBuilder.VisibleFaces[(int)Direction::Left]) {                
		m_Indices[offset++] = 8;                                         
		m_Indices[offset++] = 9;                                         
		m_Indices[offset++] = 10;                                         
		m_Indices[offset++] = 10;                                         
		m_Indices[offset++] = 11;                                         
		m_Indices[offset++] = 8;                                         
	}                                                                    
	if (cubeBuilder.VisibleFaces[(int)Direction::Right]) {               
		m_Indices[offset++] = 12;                                         
		m_Indices[offset++] = 13;                                         
		m_Indices[offset++] = 14;                                         
		m_Indices[offset++] = 14;                                         
		m_Indices[offset++] = 15;                                         
		m_Indices[offset++] = 12;                                         
	}                                                                    
	if (cubeBuilder.VisibleFaces[(int)Direction::Top]) {                 
		m_Indices[offset++] = 16;                                         
		m_Indices[offset++] = 17;                                         
		m_Indices[offset++] = 18;
		m_Indices[offset++] = 18;
		m_Indices[offset++] = 19;
		m_Indices[offset++] = 16;
	}
	if (cubeBuilder.VisibleFaces[(int)Direction::Bottom]) {
		m_Indices[offset++] = 20;
		m_Indices[offset++] = 21;
		m_Indices[offset++] = 22;
		m_Indices[offset++] = 22;
		m_Indices[offset++] = 23;
		m_Indices[offset++] = 20;
	}


	assert(offset == numIndices);
	m_IndexCount = numIndices;
	m_BufferSize = sizeof(m_Vertices);
}


Cube::~Cube()
{
}
