#version 330



layout(location = 0) in vec2 Main_Pos;	//	square in range [ -1 , +1 ]

layout(location = 1) in vec2 Inst_Min;
layout(location = 2) in vec2 Inst_Max;
layout(location = 3) in float Inst_Layer;
layout(location = 4) in vec3 Inst_Col;

out Vert_UI
{
	vec3	Col;
} vs_out;



void main()
{
	vec2 Center = (Inst_Max + Inst_Min) / 2;
	vec2 SizeHalf = (Inst_Max - Inst_Min) / 2;
	gl_Position = vec4((Main_Pos * SizeHalf) + Center, Inst_Layer, 1);

	vs_out.Col = Inst_Col;
}
