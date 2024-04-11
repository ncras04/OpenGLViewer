#version 330 core

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float attConst;
	float attLinear;
	float attQuad;
};

struct Material
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	float shininess;
};

uniform Light light;
uniform Material material;
uniform vec3 cameraPosition;

in vec3 vecNor;
in vec4 vecCol;
out vec4 fragColor;

void main()
{
	fragColor = vecCol;
}