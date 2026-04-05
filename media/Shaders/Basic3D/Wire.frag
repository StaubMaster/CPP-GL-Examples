#version 330



in Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec4 Color;
} fs_inn;



out vec4 Color;



void main()
{
	vec4 col = fs_inn.Color;

	Color = col;
}
