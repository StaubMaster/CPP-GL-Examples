#version 330



uniform sampler2DArray texture0;


in Vert_UI
{
	vec3	Tex;
	vec4	Col;
} fs_inn;

out vec4 Pixel;



void main()
{
	vec4 col = texture(texture0, fs_inn.Tex);
	if (col.a == 0) { discard; }
	Pixel = col * fs_inn.Col;
}
