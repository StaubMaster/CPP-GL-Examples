#version 330



struct SizeRatio2D
{
	vec2 Size;
	vec2 Ratio;
};

uniform SizeRatio2D ViewPortSizeRatio;

uniform sampler2DArray texture0;



in UI_Text
{
	vec2	PalletPos;
	vec2	BoundMin;
	vec2	BoundMax;
} fs_inn;

out vec4 Pixel;



void main()
{
	vec4 col = texture(texture0, vec3(fs_inn.PalletPos, 0));

	//if (col.a == 0) { discard; }
	//if (col.r >= 128) { discard; }
	//if (col.g >= 128) { discard; }
	//if (col.b >= 128) { discard; }

	if (gl_FragCoord.x >= fs_inn.BoundMin.x &&
		gl_FragCoord.x <= fs_inn.BoundMax.x &&
		gl_FragCoord.y >= fs_inn.BoundMin.y &&
		gl_FragCoord.y <= fs_inn.BoundMax.y)
	{ Pixel = col; }
	else { discard; }

}
