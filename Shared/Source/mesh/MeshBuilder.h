#pragma once
#include "Mesh.h"

// with thanks to: http://www.songho.ca/opengl/gl_sphere.html
class MeshBuilder
{
	static MeshBuilder* meshBuilder;
	Mesh* meshes[MESH_TOTAL];

	MeshBuilder();

	// generators
	Mesh* initCube();
	Mesh* initSphere();
	Mesh* initLine();
	Mesh* initQuad(int scale);

	// primitives
	void initPrimitives();

	// OBJs

	// binding
	Mesh* bindInterleavedBuffers(std::vector<float>& vertices, std::vector<int>& indices);

public:
	~MeshBuilder();
	static MeshBuilder* instance();

	void Init();
	const Mesh* getMesh(MESH_TYPES type);
};