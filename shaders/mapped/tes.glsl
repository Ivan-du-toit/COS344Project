#version 420

layout (triangles, equal_spacing) in;

uniform mat4 view;
uniform mat4 world;
uniform mat4 projection;

out vec3 v_reflect;

void main()
{
	vec3 p0 = gl_in[0].gl_Position.xyz * gl_TessCoord.x;
	vec3 p1 = gl_in[1].gl_Position.xyz * gl_TessCoord.y;
	vec3 p2 = gl_in[2].gl_Position.xyz * gl_TessCoord.z;

	vec3 position = normalize(p0 + p1 + p2);
   
	vec3 w_position = position;//(world * vec4(position, 1.0f)).xyz;
	vec3 w_normal = position;//(world * vec4(position, 1.0f)).xyz;
	
	vec3 w_eye = (inverse(view) * vec4(0,0,0,1)).xyz;
	vec3 w_view = normalize(w_position - w_eye);
	
	v_reflect = reflect(w_view, w_normal);

	gl_Position = projection * view * world * vec4(position, 1.0f);
}
