#version 330 core	
	
struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float attConst;
	float attQuad;
	float attLinear;
};

struct Material
{
	vec3 ambient; //Grundfarbe
	vec3 diffuse; //Grundfarbe
	vec3 specular; //Reflektionfarbe
	float shininess; //Intensitätswert
};

uniform Light light;
uniform Material material;
uniform vec3 cameraPosition;

uniform float time;

uniform sampler2D diffuseTexture;
uniform sampler2D overlayTexture;

in vec3 vertexPos;
in vec3 vertexNor;
in vec4 vertexCol;
in vec2 vertexUVs;

out vec4 fragColor;

uniform vec3 baseColour = vec3(0.5);

float InverseLerp(float v, float minValue, float maxValue) {
  return (v - minValue) / (maxValue - minValue);
}

float Remap(float v, float inMin, float inMax, float outMin, float outMax) {
  float t = InverseLerp(v, inMin, inMax);
	//  t = smoothstep(inMax, inMin, v);
  return mix(outMin, outMax, t);
}

vec3 CalcAmbient()
{
	return light.ambient * baseColour; 
}

vec3 CalcDiffuse()
{
	vec3 normal = normalize(vertexNor);
	vec3 lightDirection = normalize(light.position - vertexPos);
	float lightIntensity = max(dot(lightDirection, normal), 0.0);
	lightIntensity *= smoothstep(0.5, 0.505, lightIntensity);

	return (light.diffuse * lightIntensity);
}

vec3 CalcSpecular()
{
	vec3 normal = normalize(vertexNor);
	vec3 lightDirection = normalize(light.position - vertexPos);
	vec3 viewDirection = normalize(cameraPosition - vertexPos);
	vec3 reflection = reflect(-lightDirection, normal);
	float specularIntensity = pow(max(dot(viewDirection, reflection),0.0), 128.0);

	return smoothstep(0.5,0.51,(light.specular * specularIntensity));
}

float CalcFresnel()
{
	vec3 normal = normalize(vertexNor);
	vec3 viewDirection = normalize(cameraPosition - vertexPos);
	float fresnel = 1.0 - max(dot(viewDirection, normal), 0.0);
	fresnel = pow(fresnel, 2.0);
	fresnel *= step(0.5, fresnel);

	return fresnel;
}

vec3 CalcHemi()
{
  vec3 skyColor = vec3(0.0,0.3,0.6);
  vec3 groundColor = vec3(0.6,0.3,0.1);

  vec3 normal = normalize(vertexNor);
  float hemiMix = Remap(normal.y, -1.0, 1.0, 0.0, 1.0);
  return mix(groundColor, skyColor, hemiMix);
}


void main()
{
  vec3 hemi = CalcHemi();
  vec3 ambient = CalcAmbient();
  vec3 specular = CalcSpecular();
  vec3 diffuse = CalcDiffuse();
  float fresnel = CalcFresnel();

  vec3 lighting = hemi * (fresnel + 0.2) + diffuse * 0.8;

  vec3 color = baseColour * lighting + specular;

//  fragColor = vec4(color,1.0);
  fragColor = vec4(pow(color, vec3(1.0/2.2)),1.0); //Srgb unlinear
	
}

