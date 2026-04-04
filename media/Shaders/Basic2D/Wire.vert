#version 330



struct Trans2D
{
	vec2 Pos;
	mat2 Rot;
};

struct PixelSize
{
	vec2 Full;
	vec2 Half;
};
struct sDisplaySize
{
	vec2 Ratio;
	PixelSize Window;
	PixelSize Buffer;
};



uniform sDisplaySize DisplaySize;
uniform mat3 View;
uniform float Scale;



layout(location = 0) in vec2 VPos;
layout(location = 1) in vec4 VCol;

layout(location = 2) in mat3 ITrans;



out Vert {
	vec4 Col;
} vs_out;



void main()
{
	vec2 pos = VPos;
	pos = (vec3(pos, 1) * ITrans).xy;
	pos = (vec3(pos, 1) * View).xy;
	pos = pos / Scale;

	pos = pos * DisplaySize.Ratio;

	gl_Position = vec4(pos, 0, 1);

	vs_out.Col = vec4(vec3(1, 1, 1) - VCol.rgb, VCol.a);
}
