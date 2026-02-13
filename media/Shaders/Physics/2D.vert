#version 330



struct Trans2D
{
	vec2 Pos;
	mat2 Rot;
};

struct WindowBufferSize2D
{
	vec2 WindowSize;
	vec2 BufferSize;
	vec2 Ratio;
};



uniform WindowBufferSize2D WindowSize;
uniform Trans2D View;
uniform float Scale;



layout(location = 0) in vec2 VPos;
layout(location = 1) in vec4 VCol;

layout(location = 2) in vec2 IPos;
layout(location = 3) in vec2 IVel;



out Vert {
	vec4 Col;
} vs_out;



void main()
{
	vec2 pos = VPos;
	pos = pos + IPos;
	pos = (pos - View.Pos) * View.Rot;
	pos = pos * WindowSize.Ratio;
	pos = pos / Scale;

	gl_Position = vec4(pos, 0, 1);

	vs_out.Col = VCol;
}
