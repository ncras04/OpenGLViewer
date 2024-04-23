#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Input.h"
#include "Viewport.h"
#include "Time.h"
#include "glm/glm.hpp"

void SCamera::Init()
{
	position = { 0.0f, 0.0f, 2.0f };
	direction = { 0.0f, 0.0f, -1.0f };
	up = { 0.0f, 1.0f, 0.0f };

	view = glm::lookAt(position, position + direction, up);

	projection = glm::perspective(fov, (float)800 / 600, nearPlane, farPlane);
}

void SCamera::Update()
{
	glm::vec3 tmpdir = { direction.x, 0.0f, direction.z }; //fps steuerung

	if (SInput::GetKey(GLFW_KEY_W))
		Translate(tmpdir * STime::GetDeltaTime());
	if (SInput::GetKey(GLFW_KEY_S))
		Translate(-tmpdir * STime::GetDeltaTime());
	if (SInput::GetKey(GLFW_KEY_A))
		Translate(glm::normalize(glm::cross(up, tmpdir)) * STime::GetDeltaTime());
	if (SInput::GetKey(GLFW_KEY_D))
		Translate(-glm::normalize(glm::cross(up, tmpdir)) * STime::GetDeltaTime());

	glm::vec2 newMousePos = SInput::GetMousePos();

	if (m_firstMouse)
	{
		m_lastMousePos = newMousePos;
		m_firstMouse = false;
	}

	float xoffset{ newMousePos.x - m_lastMousePos.x };
	float yoffset{ m_lastMousePos.y - newMousePos.y };

	m_lastMousePos = newMousePos;
	
	float sensitifitz{ 0.1f };
	xoffset*= sensitifitz;
	yoffset *= sensitifitz;

	yaw += xoffset;
	pitch += yoffset;

	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	glm::vec3 dir{};
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	direction = glm::normalize(dir);

	view = glm::lookAt(position, position + direction, up);

}

void SCamera::Translate(glm::vec3 _dir)
{
	position += _dir;
}
