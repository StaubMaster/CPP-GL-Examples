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
/*	Main
	#---#---#---# -1
	| L | M | R |
	#---#---#---# +1
	-2  -1 +1  +2
*/
layout(location = 1) in vec3 Main_Tex;

layout(location = 2) in vec2 Inst_Pos;
layout(location = 3) in vec2 Inst_Dir;

layout(location = 4) in float Inst_Size;

out Vert_UI
{
	vec3	Tex;
} vs_out;



void main()
{
	float len = length(Inst_Dir);
	len -= Inst_Size * 2;

	float size = Inst_Size;
	if (len < 0) { size = length(Inst_Dir); }

	vec2 dirX = normalize(Inst_Dir) * Inst_Size;
	vec2 dirY = vec2(+dirX.y, -dirX.x);

	vec2 pos = Main_Pos;
//	if (Main_Pos.x < 1.0) { pos += vec2(3, 0); }
//	if (Main_Pos.x > 1.0) { pos -= vec2(3, 0); }

	pos = (dirX * pos.x) + (dirY * pos.y);
	gl_Position = vec4(pos, 0, 1);

	vs_out.Tex = Main_Tex;
}
