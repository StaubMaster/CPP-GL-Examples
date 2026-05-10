#version 330



uniform sampler2DArray texture0;



in Vert {
	vec3	Tex;
} fs_inn;



out vec4 Color;



void main()
{
	vec4 col = texture(texture0, fs_inn.Tex);
	Color = col;
}
