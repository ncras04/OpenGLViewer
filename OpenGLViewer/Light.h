#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
struct SLight
{
	const glm::vec3 position{ glm::vec3(0.0f, 0.0f, 3.0f) };
	const glm::vec3 ambient{ glm::vec3(0.5f, 0.5f, 0.5f) };
	const glm::vec3 diffuse{ glm::vec3(0.5f, 0.5f, 0.5f) };
	const glm::vec3 specular{ glm::vec3(0.5f, 0.5f, 0.5f) };

	float attenuationConst{};
	float attenuationLinear{};
	float attenuationQuad{};

	void Init(SShader*);
	void Draw();

private:

	SShader* m_shader{};
	unsigned int m_posID{}, m_ambientID{}, m_diffuseID{}, m_specularID{};
	unsigned int m_attConstID{}, m_attLinID{}, m_attQuadID{};


};

