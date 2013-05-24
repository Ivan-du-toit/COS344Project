#version 430
layout(location=0) uniform sampler2D heightMap;

uniform int fog;

in vec3 vpos;
in float distance;

out vec4 colour;

float maxFogDistance = 80.0f;
float minFogDistance = 60.0f;

void main()
{
	vec4 baseColour = texture(heightMap, vec2(vpos.x/100.0f, vpos.z/100.0f));
	
	float fogFactor = 1.0f;
	if (fog == 1)
		fogFactor = clamp((maxFogDistance - distance)/(maxFogDistance-minFogDistance), 0.0f, 1.0f); 
	vec4 fogColour = vec4(0.4);
	
	colour = baseColour* fogFactor + fogColour * (1.0f-fogFactor);
	colour.w = 1.0f;
}