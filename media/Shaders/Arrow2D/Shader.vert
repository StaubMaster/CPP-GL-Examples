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

layout(location = 2) in vec2 Inst_Pos0;
layout(location = 3) in vec2 Inst_Pos1;

layout(location = 4) in float Inst_Size;

out Vert_UI
{
	vec3	Tex;
} vs_out;



void main()
{
	vec2 pos0 = Inst_Pos0;
	vec2 pos1 = Inst_Pos1;

	vec2 dir = pos1 - pos0;
	vec2 dirX = normalize(dir);
	vec2 dirY = vec2(+dirX.y, -dirX.x);

	dirX = dirX * Inst_Size;
	dirY = dirY * Inst_Size;

	pos0 = ((pos0 / WindowSize.BufferSize) * 2) - 1; pos0.y = -pos0.y;
	pos1 = ((pos1 / WindowSize.BufferSize) * 2) - 1; pos1.y = -pos1.y;

	dirX = dirX / WindowSize.BufferSize; dirX.y = -dirX.y;
	dirY = dirY / WindowSize.BufferSize; dirY.y = -dirY.y;



	vec2 pos;

	//	Conditional stuff in Shader is Bad

	//	Middle
	if (Main_Pos.x < 0.0) { pos = Main_Pos + vec2(3, 0); }
	if (Main_Pos.x > 0.0) { pos = Main_Pos - vec2(3, 0); }

	//	Ends
	if (Main_Pos.x < -1.5) { pos = Main_Pos + vec2(4, 0); }
	if (Main_Pos.x > +1.5) { pos = Main_Pos - vec2(4, 0); }

	pos = (dirX * pos.x) + (dirY * pos.y);

	if (Main_Pos.x < 0.0) { pos += pos0; }
	if (Main_Pos.x > 0.0) { pos += pos1; }

	gl_Position = vec4(pos, 0, 1);

	vs_out.Tex = Main_Tex;
}
