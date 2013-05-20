#version 420

layout (vertices = 3) out;

float tessLevel = 1000;

void main() {
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
	
	gl_TessLevelOuter[0] = tessLevel;
	gl_TessLevelOuter[1] = tessLevel;
	gl_TessLevelOuter[2] = tessLevel;
	
	gl_TessLevelInner[0] = tessLevel;
}