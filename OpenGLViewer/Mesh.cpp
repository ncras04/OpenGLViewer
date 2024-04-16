#include "Mesh.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include<glm/gtx/transform.hpp>
#include <iostream>
#include "Camera.h"
#include "Time.h"

void SMesh::Init(SShader* _shader, SMaterial* _material)
{
	vertices = {
		{{-0.5f, -0.5f, 0.0f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f,  0.5f, 0.0f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f}},
		{{ 0.5f,  0.5f, 0.0f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f}},
		{{ 0.5f, -0.5f, 0.0f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 0.0f, 1.0f}},
	};

	indices = { 0,1,2,0,2,3 };

	shader = _shader;
	mat = _material;

	CreateBuffers();

	m_modelID = glGetUniformLocation(shader->id, "model");
	m_viewID = glGetUniformLocation(shader->id, "view");
	m_projID = glGetUniformLocation(shader->id, "projection");
	m_normalID = glGetUniformLocation(shader->id, "normal");

	m_cameraPosID = glGetUniformLocation(shader->id, "cameraPosition");

	model = glm::translate(glm::mat4{ 1.0f }, position);
	normal = glm::inverse(glm::mat3(model));

}

void SMesh::Update()
{
	Rotate(10.0f * STime::GetDeltaTime(), glm::vec3(0.0f, 1.0f, 0.0f));
}

void SMesh::Draw(const SCamera& _camera)
{
	shader->Use();
	glUniformMatrix4fv(m_modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &_camera.view[0][0]); //camera
	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]); //camera
	glUniformMatrix3fv(m_normalID, 1, GL_TRUE, &normal[0][0]);

	glUniform3fv(m_cameraPosID, 1, &(_camera.position.x));


	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void SMesh::Finalize()
{
}

void SMesh::Translate(float _x, float _y, float _z)
{
	position += glm::vec3{ _x, _y, _z };
	model = glm::translate(model, glm::vec3{ _x, _y, _z });
	normal = glm::inverse(glm::mat3(model));
}

void SMesh::Rotate(float _angle, glm::vec3 _axis)
{
	rotation += _axis * _angle;
	model = glm::rotate(model, glm::radians(_angle), _axis);
	normal = glm::inverse(glm::mat3(model));
}

void SMesh::Scale(float _x, float _y, float _z)
{
	scale += glm::vec3{ _x, _y, _z };
	model = glm::scale(model, glm::vec3{ _x, _y, _z });
	normal = glm::inverse(glm::mat3(model));
}

void SMesh::CreateBuffers()
{
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	const char* attributeName = "_pos";
	unsigned int attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuf.SetAttributeID(attributeName, attributeID);
	m_vertexBuf.CreateBufferObject();
	m_vertexBuf.Bind(GL_ARRAY_BUFFER);
	m_vertexBuf.BufferFill(sizeof(SVertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
	m_vertexBuf.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), 0);
	m_vertexBuf.EnableAttribute();

	attributeName = "_col";
	attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuf.SetAttributeID(attributeName, attributeID);
	m_vertexBuf.LinkAttribute(4, GL_FLOAT, false, sizeof(SVertex), (void*)sizeof(glm::vec3));
	m_vertexBuf.EnableAttribute();

	attributeName = "_nor";
	attributeID = shader->GetAttributeLocation(attributeName);
	m_vertexBuf.SetAttributeID(attributeName, attributeID);
	m_vertexBuf.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), (void*)(sizeof(glm::vec3)+sizeof(glm::vec4)));
	m_vertexBuf.EnableAttribute();

	m_indexBuf.CreateBufferObject();
	m_indexBuf.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuf.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
	glBindVertexArray(0);
	
}
