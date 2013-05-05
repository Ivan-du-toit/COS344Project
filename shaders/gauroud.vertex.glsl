#version 420

layout(location=0) in vec3 position;
layout(location=1) in vec3 colour;
out vec4 ex_Color;

void main(void)
{
	gl_Position = vec4(position, 1.0f);
	ex_Color = vec4(colour, 1.0f);
}