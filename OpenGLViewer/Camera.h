#pragma once
#include <glm/glm.hpp>

struct SCamera
{
	glm::vec3 position{};
	glm::vec3 direction{};
	glm::vec3 up{};

	glm::mat4 view{};
	glm::mat4 projection{};

	float nearPlane{ 0.1f }, farPlane{100.0f};
	float fov{45.0f};

	void Init();
	void Update();

	void Translate(float, float, float);



};

