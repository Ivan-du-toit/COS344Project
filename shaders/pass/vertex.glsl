#version 420

// Vertex position.
layout (location=0) in vec3 position;
layout(location=1) in vec3 colour;
//layout (location=2) in vec3 normal;

// Model-world matrix.
uniform mat4 world;
// World-view matrix.
uniform mat4 view;
// Projection matrix.
uniform mat4 projection;

out vec3 Vnormal;
out vec4 Vcolour;

void main()
{
   gl_Position = projection * view * world * vec4(position, 1.0f);
   //Vnormal = normal;
   Vcolour = vec4(colour, 1.0f);
}

