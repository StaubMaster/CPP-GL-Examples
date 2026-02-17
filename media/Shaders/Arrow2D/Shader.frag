#version 330



uniform sampler2DArray texture0;


in Vert_UI
{
	vec3	Tex;
} fs_inn;

out vec4 Pixel;



void main()
{
	Pixel = texture(texture0, fs_inn.Tex);
	//Pixel = vec4(1, 1, 1, 1);
}
