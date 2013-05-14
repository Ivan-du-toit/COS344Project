#version 420

//in vec3 Vnormal;
in vec4 Vcolour;
out vec4 colour;

void main()
{
	colour = Vcolour;
}