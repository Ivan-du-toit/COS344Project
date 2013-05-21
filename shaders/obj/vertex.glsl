#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main(){

	// Output position of the vertex, in clip space : MVP * position
	//gl_Position =  MVP*vec4(position,1);
	gl_Position = projection * view * world * vec4(position, 1.0f);
	
}

