#version 430

layout (triangles, equal_spacing) in;

layout(location=0) uniform sampler2D heightMap;

void main() {
	vec3 p0 = gl_in[0].gl_Position.xyz * gl_TessCoord.x;
	vec3 p1 = gl_in[1].gl_Position.xyz * gl_TessCoord.y;
	vec3 p2 = gl_in[2].gl_Position.xyz * gl_TessCoord.z;

	
	//vec3 position = p0 + textureSample.r + p2;
	vec3 position = p0 + p1 + p2;
	float h = texture(heightMap, vec2(position.x/1000.0f, position.z/1000.0f)).r*200;
	
	//position = normalize(position);
	//v_colour = 1.0f;
	position.y = h;
	//gl_Position = (projection * worldView * modelWorld) * vec4(position, 1.0f);
	gl_Position = vec4(position, 1.0f);
}