#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

struct SMaterial
{
	glm::vec3 ambient{ 1.0f, 1.0f, 1.0f };
	glm::vec3 diffuse{ 1.0f, 1.0f, 1.0f };
	glm::vec3 specular{ 1.0f, 1.0f, 1.0f };
	float shininess{ 32.0f };

	void Init(SShader*);
	void Draw();

private:

	SShader* m_shader{};
	STexture m_texture{}, m_texture2{};
	unsigned int matAmbientID{}, matDiffuseID{}, matSpecID{}, matShiniID{};
};

