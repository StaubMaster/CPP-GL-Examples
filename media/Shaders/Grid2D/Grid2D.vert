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
//uniform Trans2D View;
uniform mat3 View;
uniform float Scale;



layout(location = 0) in vec2 VPos;

layout(location = 1) in vec2  IPos;
layout(location = 2) in float ISize;



out Vert {
	vec4 Col;
} vs_out;



void main()
{
	vec2 pos = VPos;
	pos = (pos * ISize) + IPos;
	pos = (vec3(pos, 1) * View).xy;
	pos = pos * DisplaySize.Ratio;
	pos = pos / Scale;

	gl_Position = vec4(pos, 0, 1);

	vs_out.Col = vec4(0, 0, 0, 1);
	//vs_out.Col = vec4(0.375, 0.375, 0.375, 1);
}
