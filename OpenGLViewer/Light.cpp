#include "Light.h"

void SLight::Init(SShader* _shader)
{
	m_shader = _shader;

	m_posID = glGetUniformLocation(m_shader->id, "light.position");
	m_ambientID = glGetUniformLocation(m_shader->id, "light.ambient");
	m_diffuseID = glGetUniformLocation(m_shader->id, "light.diffuse");
	m_specularID = glGetUniformLocation(m_shader->id, "light.specular");

	m_attConstID = glGetUniformLocation(m_shader->id, "light.attConst");
	m_attLinID = glGetUniformLocation(m_shader->id, "light.attLinear");
	m_attQuadID = glGetUniformLocation(m_shader->id, "light.attQuad");
}

void SLight::Draw()
{
	m_shader->Use();
	glUniform3fv(m_posID, 1, &position.x);
	glUniform3fv(m_ambientID, 1, &ambient.x);
	glUniform3fv(m_diffuseID, 1, &diffuse.x);
	glUniform3fv(m_specularID, 1, &specular.x);

	glUniform1f(m_attConstID, attenuationConst);
	glUniform1f(m_attLinID, attenuationLinear);
	glUniform1f(m_attQuadID, attenuationQuad);
}
