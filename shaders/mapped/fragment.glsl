#version 430

layout(location=0) uniform samplerCube cubeMap;
in vec3 v_reflect;

out vec4 colour;

void main()
{
   //colour = vec4(0.0, 0.0, 0.0, 1.0);
   colour = texture(cubeMap, v_reflect.xyz);
}
