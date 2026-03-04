#version 330



uniform sampler2D texture0;



in Vert
{
	vec2	Tex;
} fs_inn;

out vec4 Pixel;



void main()
{
	vec4 col = texture(texture0, fs_inn.Tex);
	Pixel = col;
}

