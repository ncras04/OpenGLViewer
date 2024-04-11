#version 330 core
in vec3 _pos;
in vec4 _col;
in vec3 _nor;

out vec3 vertexPos;
out vec3 vertexNor;
out vec4 vertexCol;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal;

void main()
{
	vertexNor = normal * _nor;
	vertexCol = _col;
	
	vertexPos = (model * vec4(_pos, 1.0)).xyz;
	gl_Position = projection * view * model * vec4(_pos, 1.0);
}