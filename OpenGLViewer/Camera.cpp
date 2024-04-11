#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

void SCamera::Init()
{
	position = { 0.0f, 0.0f, 2.0f };
	direction = { 0.0f, 0.0f, -1.0f };
	up = { 0.0f, 1.0f, 0.0f };

	view = glm::lookAt(position, position + direction, up);

	projection = glm::perspective(fov, float(800 / 600), nearPlane, farPlane);
	//projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.f);
}

void SCamera::Update()
{
}

void SCamera::Translate(float, float, float)
{
}
