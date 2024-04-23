#include "Texture.h"

void STexture::Init(const std::string& _path, SShader* _shader)
{
	m_shader = _shader;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* buffer = stbi_load(_path.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

	if (buffer)
	{
		glGenTextures(1, &m_id);
		glBindTexture(GL_TEXTURE_2D, m_id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(buffer);

		m_texUniform = glGetUniformLocation(m_shader->id, "texture");
		glUniform1i(m_shader->id, m_texUniform);
	}
}

void STexture::Draw(unsigned int unit) const
{
	if (m_id)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}
}


