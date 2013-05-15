#version 420

// Vertex position.
layout (location=1) in vec3 position;
layout (location=2) in vec3 normal;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightView;

out vec3 Vnormal;
out vec4 v_lightPos;

out vec3 fpos;

void main()
{
	const mat4 bias = mat4(.5f, .0f, .0f, .0f, 
						   .0f, .5f, .0f, .0f,
						   .0f, .0f, .5f, .0f,
						   .5f, .5f, .5f, 1.0f);
	
	fpos = position;
	v_lightPos = (bias * projection * lightView * world * vec4(position, 1.0f));
	Vnormal = normal;
	gl_Position = projection * view * world * vec4(position, 1.0f);
}

