#version 420

layout (triangles, equal_spacing) in;

void main() {
	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;
	vec4 p2 = gl_in[2].gl_Position;

	vec3 p = gl_TessCoord.xyz; 
	gl_Position = p0*p.x + p1*p.y + p2*p.z;
}