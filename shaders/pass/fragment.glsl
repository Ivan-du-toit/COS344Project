#version 420

in vec3 Vnormal;
out vec4 colour;

void main()
{
	/*vec3 lightPosition = vec3(3, 3, 0);
	lightPosition = lightPosition - Vnormal;
	
	float intensity = dot(lightPosition, Vnormal);*/
	colour = vec4(1.0f);//vec4(0.5f, 0.6f, 0.8f, 1.0f) * 1;
}