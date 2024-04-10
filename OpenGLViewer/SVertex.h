#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
struct SVertex
{
	inline SVertex(float _x, float _y, float _z)
	{
		position = { _x, _y, _z };
	}

	glm::vec3 position;
};
#endif //!VERTEX_H

