#version 330



in Vert
{
	vec4	Col;
} fs_inn;

out vec4 Pixel;



void main()
{
	Pixel = fs_inn.Col;
}
