#ifndef MESH_H
#define MESH_H

#include <vector>
#include "SVertex.h"
#include "Shader.h"
#include "Material.h"
#include "Buffer.h"
#include "Camera.h"

struct SMesh
{
	std::vector<SVertex> vertices;
	std::vector<unsigned int> indices;

	SMaterial* mat{};
	SShader* shader{};

	void Init(SShader*, SMaterial*);

	void Update();
	void Draw(const SCamera&);
	void Finalize();

	void Translate(float, float, float);
	void Rotate(float, glm::vec3);
	void Scale(float, float, float);


	void CreateBuffers();

	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{};
	glm::vec3 rotation{};
	glm::mat4 model{};
	glm::mat3 normal{};

private:
	SBuffer  m_vertexBuf{}, m_indexBuf{};
	unsigned int m_vao{};
	unsigned int m_modelID{}, m_viewID{}, m_projID{}, m_normalID{}, m_cameraPosID{};

};

#endif //!MESH_H

