#include "Terrain.h"



Terrain::Terrain(int gridX, int gridZ, Texture texture)
{
	SIZE = 800;
}


Terrain::~Terrain()
{
}

Mesh Terrain::generateTerrain()
{
	IndexedModel model;
	int count = VERTEX_COUNT * VERTEX_COUNT;
	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j < VERTEX_COUNT; j++) {
			model.positions[vertexPointer * 3].x = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			model.positions[vertexPointer * 3 + 1].y = 0;
			model.positions[vertexPointer * 3 + 2].z = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			model.normals[vertexPointer * 3].x = 0;
			model.normals[vertexPointer * 3 + 1].y = 1;
			model.normals[vertexPointer * 3 + 2].z = 0;
			model.texCoords[vertexPointer * 2].x = (float)j / ((float)VERTEX_COUNT - 1);
			model.texCoords[vertexPointer * 2 + 1].y = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			model.indices[pointer++] = topLeft;
			model.indices[pointer++] = bottomLeft;
			model.indices[pointer++] = topRight;
			model.indices[pointer++] = topRight;
			model.indices[pointer++] = bottomLeft;
			model.indices[pointer++] = bottomRight;
		}
	}

	Mesh mesh;

	//return mesh.init(vertices, textureCoords, normals, indices);
	mesh.initModel(model);
	return mesh;
}
