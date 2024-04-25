#version 330 core
in vec3 vertexPos;

out vec4 fragColor;

uniform samplerCube cubemapTexture;

void main()
{
	fragColor = texture(cubemapTexture, vertexPos);
}