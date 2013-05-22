#version 430

in vec4 Vnormal;
out vec4 colour;

float ambient = 0.2;
float diffuse = 0.1;
float specular = 0.5;
float shininess = 200;

void main()
{
	colour = Vnormal;//vec4(Vnormal, 1.0f);
}