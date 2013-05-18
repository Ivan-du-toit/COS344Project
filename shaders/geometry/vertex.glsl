#version 420
/*
// Model-world matrix.
uniform mat4 modelWorld;
// World-view matrix.
uniform mat4 worldView;
// Projection matrix.
uniform mat4 projection;
// */
// Vertex position.
layout (location=1) in vec3 position;
// Vertex colour.
layout (location=2) in float colour;

// Colour to pass on.
//out float v_colour;

void main()
{
   //gl_Position = projection * worldView * modelWorld * vec4(position, 1.0f);
   gl_Position = vec4(position, 1.0f);
   //v_colour = colour;
}

