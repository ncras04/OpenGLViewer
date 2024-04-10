#version 330 core

in vec4 vecCol;
out vec4 fragColor;

uniform vec4 unicol;

void main()
{
	fragColor = unicol;
}