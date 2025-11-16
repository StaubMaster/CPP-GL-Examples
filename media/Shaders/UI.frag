#version 330



in Vert_UI
{
	vec3	Col;
} fs_in;

out vec4 Pixel;



void main()
{
	vec3 col = fs_in.Col;

	Pixel = vec4(col, 1);
}
