#version 330



uniform sampler2DArray texture0;


in Vert {
	vec3 Original;
	vec3 Absolute;
	vec3 Relative;

	vec3 Normal;
	vec2 Tex;
} fs_inn;



out vec4 Color;



void main()
{
	vec3 col = texture(texture0, vec3(fs_inn.Tex, 0)).rgb;

	Color = vec4(col, 1);
}
