#version 420

in vec3 Vnormal;
out vec4 out_Color;

void main(void)
{
	out_Color = vec4(Vnormal, 1.0f);
}