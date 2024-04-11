#ifndef ENGINE_H
#define ENGINE_H

#include "Viewport.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

class CEngine
{

public:
	CEngine(){}

	int Initialize(void);
	int Run(void);
	void Finalize(void);

private:

	SViewport m_viewport{};
};

#endif // !ENGINE_H

