#version 430
layout(location=0) uniform sampler2D heightMap;

in vec4 Vnormal;
in vec3 vpos;

out vec4 colour;

void main()
{

	colour = texture(heightMap, vec2(vpos.x*4.0f, vpos.z*4.0f));
	//colour = colour + (Vnormal*0.01f);
	//colour = (Vnormal);
}