#version 420

// Vertex position.
layout (location=1) in vec3 position;
layout (location=2) in vec3 normal;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

out vec4 Vnormal;
out vec3 vpos;
out float distance;

void main()
{
	Vnormal = vec4(normal, 1.0f);
	vpos = position;
	distance = length((view * world * vec4(position, 1.0f)).xyz);
	
	gl_Position = projection * view * world * vec4(position, 1.0f);
}
