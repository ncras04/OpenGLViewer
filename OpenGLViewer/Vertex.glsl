#version 330 core
in vec3 _pos;
in vec4 _col;

out vec4 vecCol;

void main()
{
	gl_Position = vec4(_pos.x, _pos.y, _pos.z, 1.0);
	vecCol = _col;
}