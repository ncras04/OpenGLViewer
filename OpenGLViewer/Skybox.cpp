#include "Skybox.h"
#include "Meshdata.h"
#include <glm/gtx/transform.hpp>

void Skybox::Init()
{
	vertices = cubeverts;
	indices = cubeindices;


	m_shader = SShader("SkyboxVert.glsl", "SkyboxFrag.glsl");

	CreateBuffers();
	m_viewID = glGetUniformLocation(m_shader.id, "view");
	m_projID = glGetUniformLocation(m_shader.id, "projection");

	const char* chars[]{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg",
	};

	glGenTextures(1, &m_texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);

	stbi_set_flip_vertically_on_load(false);

	for (unsigned int i = 0; i < 6; i++)
	{
		int width{}, height{}, bitsPerPixel{};
		unsigned char* buffer = stbi_load(chars[i], &width, &height, &bitsPerPixel, 0);

		if (buffer)
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);

			stbi_image_free(buffer);
		}
		else
		{
			stbi_image_free(buffer);
			std::cout << "failed" << std::endl;
		}
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	m_shader.Use();
	m_texUniform = glGetUniformLocation(m_shader.id, "cubemapTexture");
	glUniform1i(m_texUniform, m_unit);
}

void Skybox::Draw(const SCamera& _camera)
{
	m_shader.Use();

	GLint oldFaceMode{};
	glGetIntegerv(GL_CULL_FACE_MODE, &oldFaceMode);
	GLint oldDepthMode{};
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthMode);

	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texID);

	glm::mat4 view = glm::lookAt(glm::vec3(0.0f), _camera.direction, _camera.up);

	glUniformMatrix4fv(m_viewID, 1, GL_FALSE, &view[0][0]); //camera
	glUniformMatrix4fv(m_projID, 1, GL_FALSE, &_camera.projection[0][0]); //camera

	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glCullFace(oldFaceMode);
	glDepthFunc(oldDepthMode);

}

void Skybox::CreateBuffers()
{
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	const char* attributeName = "_pos";
	unsigned int attributeID = m_shader.GetAttributeLocation(attributeName);
	m_vertexBuf.SetAttributeID(attributeName, attributeID);
	m_vertexBuf.CreateBufferObject();
	m_vertexBuf.Bind(GL_ARRAY_BUFFER);
	m_vertexBuf.BufferFill(sizeof(SVertex) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);
	m_vertexBuf.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), 0);
	m_vertexBuf.EnableAttribute();

	attributeName = "_col";
	attributeID = m_shader.GetAttributeLocation(attributeName);
	m_vertexBuf.SetAttributeID(attributeName, attributeID);
	m_vertexBuf.LinkAttribute(4, GL_FLOAT, false, sizeof(SVertex), (void*)sizeof(glm::vec3));
	m_vertexBuf.EnableAttribute();

	attributeName = "_nor";
	attributeID = m_shader.GetAttributeLocation(attributeName);
	m_vertexBuf.SetAttributeID(attributeName, attributeID);
	m_vertexBuf.LinkAttribute(3, GL_FLOAT, false, sizeof(SVertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4)));
	m_vertexBuf.EnableAttribute();

	attributeName = "_uvs";
	attributeID = m_shader.GetAttributeLocation(attributeName);
	m_vertexBuf.SetAttributeID(attributeName, attributeID);
	m_vertexBuf.LinkAttribute(2, GL_FLOAT, false, sizeof(SVertex), (void*)(sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec3)));
	m_vertexBuf.EnableAttribute();

	m_indexBuf.CreateBufferObject();
	m_indexBuf.Bind(GL_ELEMENT_ARRAY_BUFFER);
	m_indexBuf.BufferFill(sizeof(unsigned int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}
