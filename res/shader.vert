#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;

const float PI = 3.1415926535897932384626433832795;

const float waveLength = 20.0;
const float waveAmplitude = 1.2;
const float height = 0;
const float specularReflectivity = 0.86;
const float shineDamper = 2.8;

out vec3 Normal;
out vec3 Position;
out vec3 pass_toCameraVector;
out vec3 pass_specular;
out vec3 pass_diffuse;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float waveTime;

uniform vec3 cameraPos;
uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec2 lightBias;

vec3 calcSpecularLighting(vec3 toCamVector, vec3 toLightVector, vec3 normal){
	vec3 reflectedLightDirection = reflect(-toLightVector, normal);
	float specularFactor = dot(reflectedLightDirection , toCamVector);
	specularFactor = max(specularFactor,0.0);
	specularFactor = pow(specularFactor, shineDamper);
	return specularFactor * specularReflectivity * lightColour;
}

vec3 calculateDiffuseLighting(vec3 toLightVector, vec3 normal){
	float brightness = max(dot(toLightVector, normal), 0.0);
	return (lightColour * lightBias.x) + (brightness * lightColour * lightBias.y);
}

float generateOffset(float x, float z)
{
	float radiansX = (x / waveLength + waveTime) * 2.0 * PI;
	float radiansZ = (z / waveLength + waveTime) * 2.0 * PI;
	return waveAmplitude * 0.5 * (sin(radiansZ) + cos(radiansX));
}

vec3 applyDistortion(vec3 vertex){
	float xDistortion = generateOffset(vertex.x, vertex.z);
	float yDistortion = generateOffset(vertex.x, vertex.z);
	float zDistortion = generateOffset(vertex.x, vertex.z);
	return vertex + vec3(0, yDistortion, 0);
}

void main()
{
	vec3 currentVertex = vec3(aPos.x, height, aPos.z);

	currentVertex = applyDistortion(currentVertex);

	Normal = mat3(transpose(inverse(model))) * aNormal;
    Position = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(currentVertex, 1.0);

	pass_toCameraVector = normalize(cameraPos - currentVertex);

	vec3 toLightVector = -normalize(lightDirection);
	pass_specular = calcSpecularLighting(pass_toCameraVector, toLightVector, aNormal);
	pass_diffuse = calculateDiffuseLighting(toLightVector, aNormal);
}
