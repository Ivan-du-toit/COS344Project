#version 420

in vec4 normal;
in vec4 ex_Color;
out vec4 out_Color;

float ambient = 0.1;
float diffuse = 0.3;
float specular = 0.3;
float shininess = 200;

void main(void)
{
	vec3 n;
	n.x = normal.x;
	n.y = normal.y;
	n.z = normal.z;
	vec3 lightPosition = vec3(-3, 1, 0.5);
	lightPosition = lightPosition - n;
	
	vec3 view = vec3(0, 0, 1);
	
	vec3 reflection = 2 * (max((dot(lightPosition, n)), 0.0f)) * n - lightPosition;
	reflection = normalize(reflection);
	
	float factor = ambient + diffuse * max((dot(lightPosition, n)), 0.0f) + specular * pow(max(dot(reflection, view), 0.0f), shininess);

	out_Color = factor * ex_Color;
	out_Color.w = 1.0f;
}