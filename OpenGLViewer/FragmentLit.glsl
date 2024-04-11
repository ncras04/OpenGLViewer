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

in vec3 vertexPos;
in vec3 vertexNor;
in vec4 vertexCol;

out vec4 fragColor;

vec3 CalcAmbient()
{
	return light.ambient * vec3(vertexCol); //material.ambient;
}

vec3 CalcDiffuse()
{
	vec3 normal = normalize(vertexNor);
	vec3 lightDirection = normalize(light.position - vertexPos);
	float lightIntensity = max(dot(lightDirection, normal), 0.0);

	return light.diffuse * material.diffuse * lightIntensity;
}

vec3 CalcSpecular()
{
	vec3 normal = normalize(vertexNor);
	vec3 lightDirection = normalize(light.position - vertexPos);
	vec3 viewDirection = normalize(cameraPosition - vertexPos);
	vec3 reflection = reflect(-lightDirection, normal);
	float specular = pow(max(dot(viewDirection, reflection),0.0), material.shininess);

	return light.specular * material.shininess * specular;
}

float CalcAttenuation()
{
	float dist = length(light.position - vertexPos);
	return 1.0 / ( light.attConst 
				+( light.attLinear * dist)
				+( light.attQuad * dist * dist));
}

void main()
{
	vec3 ambient = CalcAmbient();
	vec3 diffuse = CalcDiffuse();
	vec3 specular = CalcSpecular();

	float attenuation = CalcAttenuation();

	vec4 col = vec4(attenuation * (ambient + diffuse + specular), 1.0);

	fragColor = col;
}