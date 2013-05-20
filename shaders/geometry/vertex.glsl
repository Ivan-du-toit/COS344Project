#version 420

layout (location=1) in vec3 position;
layout (location=2) in vec3 normal;

void main()
{
   gl_Position = vec4(position, /*max(normal.z, */1.0f/*)*/);
}

