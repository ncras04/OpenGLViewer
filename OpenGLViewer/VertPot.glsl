#version 330 core
in vec3 _pos;
in vec4 _col;
in vec3 _nor;
in vec2 _uvs;

out vec3 vertexPos;
out vec3 vertexNor;
out vec4 vertexCol;
out vec2 vertexUVs;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal;

void main()
{
	vertexNor = normal * _nor;
	vertexCol = _col;
	vertexUVs = _uvs;
	
	vertexPos = (model * vec4(_pos, 1.0)).xyz;
	gl_Position = projection * view * model * vec4(_pos, 1.0);
}