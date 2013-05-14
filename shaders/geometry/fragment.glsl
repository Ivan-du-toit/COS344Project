#version 420

//in float v_colour;

in vec3 normal;
out vec4 colour;

void main()
{
	vec3 lightPosition = vec3(3, 3, 0);
	lightPosition = lightPosition - normal;
	
	float intensity = dot(lightPosition, normal);
	colour = vec4(0.5f, 0.6f, 0.8f, 1.0f) *intensity;
}