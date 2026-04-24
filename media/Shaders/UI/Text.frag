#version 330



uniform sampler2DArray texture0;



in UI_Text
{
	vec2	PalletPos;
	vec2	BoundMin;
	vec2	BoundMax;
	vec4	Color;
} fs_inn;



out vec4 Color;



void main()
{
	vec4 col = texture(texture0, vec3(fs_inn.PalletPos, 0));

	if (col.a == 0) { discard; }
	if (col.r >= 0.5) { discard; }
	if (col.g >= 0.5) { discard; }
	if (col.b >= 0.5) { discard; }

//	col = vec4(1, 1, 1, 1);
	col = col.a * fs_inn.Color;

	if (gl_FragCoord.x >= fs_inn.BoundMin.x &&
		gl_FragCoord.x <= fs_inn.BoundMax.x &&
		gl_FragCoord.y >= fs_inn.BoundMin.y &&
		gl_FragCoord.y <= fs_inn.BoundMax.y)
	{ Color = col; } else { discard; }

	//Color = col;
}
