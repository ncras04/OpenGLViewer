#pragma once
#include <glm/glm.hpp>
#include <iostream>

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

	void Translate(glm::vec3 _dir);

private:
	bool m_firstMouse{ true };
	glm::vec2 m_lastMousePos;

	float yaw{-90.0f};
	float pitch{};

};

