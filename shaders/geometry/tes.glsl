#version 420
 
layout(triangles,equal_spacing) in;
 
void main(void) {
	vec3 p0 = gl_in[0].gl_Position.xyz * gl_TessCoord.x;
	vec3 p1 = gl_in[1].gl_Position.xyz * gl_TessCoord.y;
	vec3 p2 = gl_in[2].gl_Position.xyz * gl_TessCoord.z;

	vec3 position = p0 + p1 + p2;
	gl_Position = vec4(position, 1.0f);
}