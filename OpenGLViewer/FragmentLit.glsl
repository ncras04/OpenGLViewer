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

vec3 CalcAmbient()
{
	return light.ambient * texture(diffuseTexture,vertexUVs).xyz; //material.ambient;
}

vec3 CalcDiffuse()
{
	vec3 normal = normalize(vertexNor);
	vec3 lightDirection = normalize(light.position - vertexPos);
	float lightIntensity = max(dot(lightDirection, normal), 0.0);

	return light.diffuse * (texture(diffuseTexture,vertexUVs).xyz * lightIntensity); //material.diffuse
}

vec3 CalcSpecular()
{
	vec3 normal = normalize(vertexNor);
	vec3 lightDirection = normalize(light.position - vertexPos);
	vec3 viewDirection = normalize(cameraPosition - vertexPos);
	vec3 reflection = reflect(-lightDirection, normal);
	float specularIntensity = pow(max(dot(viewDirection, reflection),0.0), material.shininess);

	return light.specular * (texture(diffuseTexture,vertexUVs).xyz * specularIntensity);
}

float CalcAttenuation()
{
	float dist = length(light.position - vertexPos);
	return 1.0 / ( light.attConst 
				+( light.attLinear * dist)
				+( light.attQuad * dist * dist));
}


float near = 0.1; 
float far  = 10.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
	vec3 ambient = CalcAmbient();
	vec3 diffuse = CalcDiffuse();
	vec3 specular = CalcSpecular();

	float attenuation = CalcAttenuation();

	vec4 col = vec4(attenuation * (ambient + diffuse + specular), 1.0);

//	-- Simple col fragColor
	
	fragColor = col;

	vec4 diffTex = texture(diffuseTexture,vertexUVs);
	vec4 overlayTex = texture(overlayTexture, vertexUVs);

//--- Simple Overlay Mix
//fragColor = mix(diffTex,overlayTex, overlayTex.w);

//---Smoothstep Logo with vignette
//	float stepping = step(0.5, vertexUVs.x);
//	float smoothstepping = smoothstep(0.25,0.75,vertexUVs.x);
//
//	float line = smoothstep(0.5, 0.0, abs(vertexUVs.y - 0.5));
//
//	fragColor = col * mix(mix(diffTex, overlayTex, line), overlayTex, overlayTex.w);

//----Mario Effekt
//	float distToCenter = length(vertexUVs - 0.5);
//	float d = sin(distToCenter * 50.0 - time * 2.0);
//	vec2 dir = normalize(vertexUVs - 0.5);
//	vec2 ripples = vertexUVs + d * dir * 0.05;
//
//	vec4 painting = texture(diffuseTexture,ripples);
//
//	float alpha = step(0.001, overlayTex.w);
//
//	fragColor = mix(painting,overlayTex, alpha);

//-----Pixelize
//	vec2 dimensions = vec2(64.0, 64.0);
//	vec2 texUV = floor(vertexUVs * dimensions) / dimensions;
//	vec3 pixel = texture(diffuseTexture, texUV).xyz;
//
//	fragColor = texture(diffuseTexture, texUV);

//-----Blending via Vertex Coloring

//fragColor = col * clamp((diffTex * vertexCol.x) + (overlayTex * vertexCol.z),0.0,1.0);

//-----Vertex UV Coloring
//	fragColor = vec4(vertexUVs.x, vertexUVs.y, 0.0, 1.0);
//-----Depth??
//	float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
//    fragColor = vec4(vec3(depth), 1.0);
}