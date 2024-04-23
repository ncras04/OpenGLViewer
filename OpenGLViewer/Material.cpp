#include "Material.h"

void SMaterial::Init(SShader* _shader)
{
	m_shader = _shader;

	matAmbientID = glGetUniformLocation(m_shader->id, "material.ambient");
	matDiffuseID = glGetUniformLocation(m_shader->id, "material.diffuse");
	matSpecID = glGetUniformLocation(m_shader->id, "material.specular");
	matShiniID = glGetUniformLocation(m_shader->id, "material.shininess");

	m_texture.Init("container.jpg", m_shader, "diffuseTexture", 0);
	m_texture2.Init("SAELogo.png", m_shader, "overlayTexture", 1);
}

void SMaterial::Draw()
{
	m_shader->Use();

	m_texture.Draw();
	m_texture2.Draw();

	glUniform3fv(matAmbientID, 1, &ambient.x);
	glUniform3fv(matDiffuseID, 1, &diffuse.x);
	glUniform3fv(matSpecID, 1, &specular.x);
	glUniform1f(matShiniID, shininess);

}
