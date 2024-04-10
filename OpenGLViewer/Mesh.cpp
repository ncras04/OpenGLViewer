#include "Mesh.h"
#include <iostream>

void SMesh::Init(SShader* _shader, SMaterial* _material)
{
	vertices = {
		{-0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f}
	};

	indices = { 0,1,2,0,2,3 };

	shader = _shader;
	mat = _material;

	CreateBuffers();
}

void SMesh::Update()
{
}

void SMesh::Draw()
{
	shader->Use();
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void SMesh::Finalize()
{
}

void SMesh::CreateBuffers()
{
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);


	const char* attributeName = "aPos";
	unsigned int attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuf.SetAttributeID(attributeName, attributeID);
	m_vertexBuf.CreateBufferObject();
	m_vertexBuf.Bind(GL_ARRAY_BUFFER);
	m_vertexBuf.BufferFill(sizeof(SVertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
	m_vertexBuf.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), 0);
	m_vertexBuf.EnableAttribute();

	m_indexBuf.CreateBufferObject();
	m_indexBuf.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuf.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
	glBindVertexArray(0);
	
}
