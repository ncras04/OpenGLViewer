#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
struct SVertex
{
	inline SVertex(float _x, float _y, float _z)
	{
		position = { _x, _y, _z };
		color = { 1.0f, 0.5f, 1.0f, 1.0f };
	}

	inline SVertex(glm::vec3 _pos, glm::vec4 _col)
	{
		position = _pos;
		color = _col;
	}

	glm::vec3 position;
	glm::vec4 color;
};
#endif //!VERTEX_H

