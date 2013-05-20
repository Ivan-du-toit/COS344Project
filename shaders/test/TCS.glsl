#version 420

layout (vertices = 3) out;

void main() {
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	
	gl_TessLevelOuter[0] = 1.0f;
	gl_TessLevelOuter[1] = 1.0f;
	gl_TessLevelOuter[2] = 1.0f;
	
	gl_TessLevelInner[0] = 1.0f;
	gl_TessLevelInner[1] = 1.0f;
}