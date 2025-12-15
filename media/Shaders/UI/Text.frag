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

	vec2 pos = gl_FragCoord.xy / 2;	//	only on Mac, because FrameBufferSize != WindowSize

	if (col.a == 0) { discard; }

	if (pos.x >= fs_inn.BoundMin.x &&
		pos.x <= fs_inn.BoundMax.x &&
		pos.y >= fs_inn.BoundMin.y &&
		pos.y <= fs_inn.BoundMax.y)
	{ Pixel = vec4(col); }
	else { discard; }

}
