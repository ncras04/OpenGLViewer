#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Shader.h"
#include "stb_image.h"

struct STexture
{
	inline ~STexture() { glDeleteTextures(1, &m_id); m_shader = nullptr; };

	inline int GetWidth() const { return m_width; };
	inline int GetHeight() const { return m_height; };

	void Draw();
	void Init(const std::string& _path, SShader* _shader, const char* _uName, int _unit);

private:
	SShader* m_shader{};
	unsigned int m_id{};
	unsigned int m_texUniform{};
	std::string m_path{};
	int m_width{}, m_height{}, m_bitsPerPixel{}, m_unit{};

};
