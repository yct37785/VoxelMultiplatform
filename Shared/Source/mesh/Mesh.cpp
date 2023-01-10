#include "Mesh.h"

Mesh::Mesh()
{
	VBO = EBO = VAO = totalVertices = 0;
}

Mesh::Mesh(unsigned int VBO, unsigned int EBO, unsigned int VAO, int totalVertices)
{
	this->VBO = VBO;
	this->EBO = EBO;
	this->VAO = VAO;
	this->totalVertices = totalVertices;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

unsigned int Mesh::getVBO() const
{
	return VBO;
}

unsigned int Mesh::getEBO() const
{
	return EBO;
}

unsigned int Mesh::getVAO() const
{
	return VAO;
}

int Mesh::getTotalVertices() const
{
	return totalVertices;
}
