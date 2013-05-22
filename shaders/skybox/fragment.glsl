#version 430

layout(location=0) uniform samplerCube cubeMap;
in vec4 Vnormal;
in vec3 vpos;

out vec4 colour;

void main()
{
	//colour = Vnormal;//vec4(Vnormal, 1.0f);
	
	colour = texture(cubeMap, vpos);// + (Vnormal * 0.1f);
}