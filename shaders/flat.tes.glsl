#version 420

layout (triangles, equal_spacing) in;

uniform mat4 view;
uniform mat4 world;
uniform mat4 projection;

out vec4 ex_Color;
flat out vec4 normal;

void main() {
	vec3 p0 = gl_in[0].gl_Position.xyz * gl_TessCoord.x;
	vec3 p1 = gl_in[1].gl_Position.xyz * gl_TessCoord.y;
	vec3 p2 = gl_in[2].gl_Position.xyz * gl_TessCoord.z;

	vec3 position = p0 + p1 + p2;
	position = normalize(position);
	normal = vec4(position, 0.0);
	normal = world*normal;
	ex_Color = vec4(position, 1.0f);
	gl_Position = (projection * view * world) * vec4(position, 1.0f);
}