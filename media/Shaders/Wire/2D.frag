#version 330



in Vert
{
	vec4	Col;
} fs_inn;

out vec4 Pixel;



void main()
{
	Pixel = vec4(1, 1, 1, 1) - fs_inn.Col;
}
