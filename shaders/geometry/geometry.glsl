#version 420

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

out vec3 normal;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 p0 = gl_in[0].gl_Position;
	vec4 p1 = gl_in[1].gl_Position;
	vec4 p2 = gl_in[2].gl_Position;
	
	vec4 v0 = p1 - p0;
	vec4 v1 = p2 - p0;
	
	normal = normalize(cross(v0.xyz, v1.xyz));
	
	gl_Position = projection * view * p0;
	EmitVertex();
	
	gl_Position = projection * view * p1;
	EmitVertex();
	
	gl_Position = projection * view * p2;
	EmitVertex();
	
	
	EndPrimitive();
   //gl_Position = (projection * view * world) * vec4(position, 1.0f);
}
