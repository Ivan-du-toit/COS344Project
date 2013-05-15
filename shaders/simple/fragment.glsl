#version 430

in vec4 v_lightPos;
in vec3 Vnormal;
out vec4 colour;
in vec3 fpos;

float ambient = 0.2;
float diffuse = 0.1;
float specular = 0.5;
float shininess = 200;

void main()
{
	vec3 reflection = 2 * (max((dot(v_lightPos.xyz, Vnormal)), 0.0f)) * Vnormal - v_lightPos.xyz;
	reflection = normalize(reflection);
	
	float factor = ambient + diffuse * max((dot(v_lightPos.xyz, Vnormal)), 0.0f); + specular * pow(max(dot(reflection, v_lightPos.xyz), 0.0f), shininess);
	colour = vec4(1.0f)*factor;
}