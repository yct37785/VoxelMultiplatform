#pragma once
#include "../Utility.h"

/*
* VBO, EBO and VAO
* vertices, texcoords, normals etc
* attach textures separately
*/
class Mesh
{
	unsigned int VBO, EBO, VAO;
	int totalVertices;

public:
	Mesh();
	Mesh(unsigned int VBO, unsigned int EBO, unsigned int VAO, int totalVertices);
	~Mesh();

	unsigned int getVBO() const;
	unsigned int getEBO() const;
	unsigned int getVAO() const;
	int getTotalVertices() const;
};