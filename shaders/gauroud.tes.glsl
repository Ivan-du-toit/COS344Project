#version 420

layout (triangles, equal_spacing) in;

uniform mat4 view;
uniform mat4 world;
uniform mat4 projection;

out vec4 normal;
out vec4 ex_Color;

float ambient = 0.2;
float diffuse = 0.5;
float specular = 0.5;
float shininess = 200;

void main() {
	vec3 p0 = gl_in[0].gl_Position.xyz * gl_TessCoord.x;
	vec3 p1 = gl_in[1].gl_Position.xyz * gl_TessCoord.y;
	vec3 p2 = gl_in[2].gl_Position.xyz * gl_TessCoord.z;

	vec3 position = p0 + p1 + p2;
	position = normalize(position);
	normal = vec4(position, 0.0);
	normal = world*normal;
	
	vec3 n;
	n.x = normal.x;
	n.y = normal.y;
	n.z = normal.z;
	vec3 lightPosition = vec3(0, 3, 2);
	lightPosition = lightPosition - n;
	
	vec3 camera = vec3(0, 0, 1);
	
	vec3 reflection = 2 * (max((dot(lightPosition, n)), 0.0f)) * n - lightPosition;
	reflection = normalize(reflection);
	
	float factor = ambient + diffuse * max((dot(lightPosition, n)), 0.0f) + specular * pow(max(dot(reflection, camera), 0.0f), shininess);
	
	ex_Color = factor * vec4(position, 1.0f);
	gl_Position = (projection * view * world) * vec4(position, 1.0f);
}