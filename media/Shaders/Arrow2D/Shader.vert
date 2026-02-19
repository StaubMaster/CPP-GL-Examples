#version 330



struct Trans2D
{
	vec2 Pos;
	mat2 Rot;
};

struct DisplaySize
{
	vec2 WindowSize;
	vec2 BufferSize;
	vec2 Ratio;
};

uniform DisplaySize WindowSize;
uniform Trans2D View;
uniform float Scale;



layout(location = 0) in vec2 Main_Pos;
layout(location = 1) in vec3 Main_Tex;

layout(location = 2) in vec2 Inst_Pos0;
layout(location = 3) in vec2 Inst_Pos1;

layout(location = 4) in float Inst_Size;
layout(location = 5) in vec4 Inst_Col;

out Vert_UI
{
	vec3	Tex;
	vec4	Col;
} vs_out;



void main()
{
	vec2 pos0 = Inst_Pos0;
	vec2 pos1 = Inst_Pos1;

	pos0 = (pos0 - View.Pos) * View.Rot;
	pos1 = (pos1 - View.Pos) * View.Rot;

	pos0 = pos0 * WindowSize.Ratio;
	pos1 = pos1 * WindowSize.Ratio;

	pos0 = pos0 / Scale;
	pos1 = pos1 / Scale;

	//	Normal to Pixel
	vec2 dir = (pos1 - pos0) * WindowSize.BufferSize;
	vec2 dirX = normalize(dir) * Inst_Size;
	vec2 dirY = vec2(+dirX.y, -dirX.x);

	//	Pixel to Normal
	dirX /= WindowSize.BufferSize;
	dirY /= WindowSize.BufferSize;



	//	Conditional stuff in Shader is Bad
	vec2 pos;

	//	Middle
	if (Main_Pos.x < 0.0) { pos = Main_Pos + vec2(3, 0); }
	if (Main_Pos.x > 0.0) { pos = Main_Pos - vec2(3, 0); }

	pos = (dirX * pos.x) + (dirY * pos.y);

	if (Main_Pos.x < 0.0) { pos += pos0; }
	if (Main_Pos.x > 0.0) { pos += pos1; }

	gl_Position = vec4(pos, 0, 1);

	vs_out.Tex = Main_Tex;
	vs_out.Col = Inst_Col;
}
