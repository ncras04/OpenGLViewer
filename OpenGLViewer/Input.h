#ifndef INPUT_H
#define INPUT_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

struct SInput
{
	static void Init(GLFWwindow* _window);
	static bool GetKey(int _key);
	static glm::vec2 GetMousePos();

private: 
	static GLFWwindow* m_window;
};

#endif // !INPUT_H

