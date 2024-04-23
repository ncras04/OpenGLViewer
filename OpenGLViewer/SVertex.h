#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
struct SVertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal;
	glm::vec2 uvs;
};
#endif //!VERTEX_H

