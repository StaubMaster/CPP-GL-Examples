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
uniform Trans2D View;
uniform float Scale;



layout(location = 0) in vec2 VPos;
layout(location = 1) in vec4 VCol;

layout(location = 2) in vec2 IPos;
layout(location = 3) in mat2 IRot;

//layout(location = 5) in vec2 IVelPos;
//layout(location = 6) in mat2 IVelRot;



out Vert {
	vec4 Col;
} vs_out;



void main()
{
	vec2 pos = VPos;
	pos = (pos * transpose(IRot)) + IPos;
	pos = (pos - View.Pos) * View.Rot;
	pos = pos * DisplaySize.Ratio;
	pos = pos / Scale;

	gl_Position = vec4(pos, 0, 1);

	vs_out.Col = VCol;
}
