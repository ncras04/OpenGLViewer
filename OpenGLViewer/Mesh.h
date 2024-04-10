#ifndef MESH_H
#define MESH_H

#include <vector>
#include "SVertex.h"
#include "Shader.h"
#include "SMaterial.h"
#include "Buffer.h"

struct SMesh
{
	std::vector<SVertex> vertices;
	std::vector<unsigned int> indices;

	SMaterial* mat{};
	SShader* shader{};

	void Init(SShader*, SMaterial*);

	void Update();
	void Draw();
	void Finalize();

	void CreateBuffers();

	//modelmatrix, rot,pos,scale (Transform)
	//translate rotate scale methode

private: 
	SBuffer m_vertexBuf{}, m_indexBuf{};
	unsigned int m_vao{};
};

#endif //!MESH_H

