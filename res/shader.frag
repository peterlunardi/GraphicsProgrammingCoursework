#version 330 core
out vec4 FragColor;

const float fresnelReflective = 0.4;
const vec3 waterColour = vec3(0.301, 0.731, 0.877);

in vec3 Normal;
in vec3 Position;
in vec3 pass_specular;
in vec3 pass_diffuse;
in vec3 pass_toCameraVector;

uniform vec3 cameraPos;
uniform samplerCube skybox;

float calculateFresnel(){
	vec3 viewVector = normalize(pass_toCameraVector);
	vec3 normal = normalize(Normal);
	float refractiveFactor = dot(viewVector, normal);
	refractiveFactor = pow(refractiveFactor, fresnelReflective);
	return clamp(refractiveFactor, 0.0, 1.0);
}

void main()
{

	vec4 blue = vec4(0.0, 0.1, 0.2, 1.0);

	vec3 refractColor;
	float ratio = 1.00 / 1.01;
	vec3 a = normalize(Position - cameraPos);
	vec3 b = refract(a, normalize(Normal), ratio);
	refractColor = texture(skybox, b).rgb;

	vec3 reflectColor;
	vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
	reflectColor = texture(skybox, R).rgb;

	vec3 finalColour = mix(reflectColor, refractColor, calculateFresnel());
	finalColour = finalColour * pass_diffuse + pass_specular;
	finalColour = mix(finalColour, waterColour, 0.234);

    FragColor =  vec4(finalColour, clamp(1 - calculateFresnel(), 0.4, 1.0));
} 

