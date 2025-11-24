#version 330



uniform sampler2DArray texture0;



in UI_Text
{
	vec2	PalletPos;
} fs_inn;

out vec4 Pixel;



void main()
{
	vec4 col = texture(texture0, vec3(fs_inn.PalletPos, 0));

	if (col.a == 0) { discard; }
	Pixel = vec4(col);
}
