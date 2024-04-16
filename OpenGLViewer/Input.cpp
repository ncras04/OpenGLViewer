#include "Input.h"

GLFWwindow* SInput::m_window{};

void SInput::Init(GLFWwindow* _window)
{
	m_window = _window;
}

bool SInput::GetKey(int _key)
{
	if (m_window)
		return glfwGetKey(m_window, _key) == GLFW_PRESS;

	return false;
}

glm::vec2 SInput::GetMousePos()
{
	double xpos{};
	double ypos{};

	if (m_window)
		glfwGetCursorPos(m_window, &xpos, &ypos);

	return { xpos, ypos };
}
