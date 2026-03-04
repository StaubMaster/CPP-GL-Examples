#version 330



layout(location = 0) in vec2 Main_Pos;
layout(location = 1) in vec2 Main_Tex;

layout(location = 2) in vec2 Inst_Pos;

out Vert
{
	vec2	Tex;
} vs_out;



void main()
{
	vec2 pos = Main_Pos;
	pos += Inst_Pos;
	gl_Position = vec4(pos, 0, 1);

	vs_out.Tex = Main_Tex;
}
