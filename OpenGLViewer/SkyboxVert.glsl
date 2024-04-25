#version 330 core
in vec3 _pos;

out vec3 vertexPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	vertexPos = _pos;
	gl_Position = (projection * view * vec4(_pos, 1.0)).xyww;
}