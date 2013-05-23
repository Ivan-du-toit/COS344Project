#version 430
layout(location=0) uniform sampler2D heightMap;

in vec3 vpos;

out vec4 colour;

void main()
{
	colour = texture(heightMap, vec2(vpos.x/100.0f, vpos.z/100.0f));
	//colour = vec4(1.0f);
}