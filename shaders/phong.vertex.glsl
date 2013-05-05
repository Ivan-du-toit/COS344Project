#version 420

layout(location=0) in vec3 position;
layout(location=1) in vec3 colour;
layout(location=2) in vec3 normal;

out vec4 ex_Color;

void main(void)
{
	gl_Position = vec4(position, 1.0f);
	position = normal;
	//gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * vec4(position, 1.0f);
	ex_Color = vec4(colour, 1.0f);
}