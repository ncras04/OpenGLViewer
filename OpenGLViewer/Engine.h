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


	//std::vector<Vertex> m_vertices = std::vector<Vertex>{
	//	// x     y     z
	//	Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)}, // links-unten
	//	Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)}, // rechts-unten
	//	Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)}, // oben-links
	//	Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // oben-links

	//};

	//std::vector<unsigned int> m_indices = std::vector<unsigned int>{
	//	0, 1, 2, //1. Dreieck des Face
	//	2, 1, 3  //2. Dreieck des Face
	//};
};

#endif // !ENGINE_H

