#version 420

layout(location=0) in vec3 position;
layout(location=1) in vec3 colour;
layout(location=2) in vec3 normal;

out vec4 ex_Color;
out vec3 Vnormal;

void main(void)
{
	gl_Position = vec4(position, 1.0f);
	//vec3 Vnormal;
	Vnormal = normal;
	//gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * vec4(position, 1.0f);
	colour = colour*Vnormal;
	ex_Color = vec4(colour*normal, 1.0f);
}