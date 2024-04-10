#include "Mesh.h"

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

    glGenBuffers(1, &m_vertexBuf); //generiere buffer id

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuf); //binde id mit einem typ buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    //kopiere daten auf gpu von cpu //Hint: Static Draw is set only once and used may times

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertex), (void*)0); //Tells gpu how to interpret data
    //takes data from memory managed by vbo (can have multiple vbo) bound to array:buffer)
    glEnableVertexAttribArray(0); //0 steht für location 0 im vertex shader;




	//const char* attributeName = "aPos";
	//unsigned int attributeID = shader->GetAttributeLocation(attributeName);
	//m_vertexBuf.SetAttributeID(attributeName, attributeID);
	//m_vertexBuf.CreateBufferObject();
	//m_vertexBuf.Bind(GL_ARRAY_BUFFER);
	//m_vertexBuf.BufferFill(sizeof(vertices), &(vertices), GL_STATIC_DRAW);
	//m_vertexBuf.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), (void*)0);
	//m_vertexBuf.EnableAttribute();

	glGenBuffers(1, &m_indexBuf); //generiere buffer id
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), & indices, GL_STATIC_DRAW);
	//m_indexBuf.BufferFill(sizeof(indices), &(indices), GL_STATIC_DRAW);

	glBindVertexArray(0);
	
}
