#version 330



struct SizeRatio2D
{
	vec2 Size;
	vec2 Ratio;
};

uniform SizeRatio2D ViewPortSizeRatio;



layout(location = 0) in vec2 Main_Pos;	//	square in range [ -1 , +1 ]

layout(location = 1) in vec2 Inst_Min;
layout(location = 2) in vec2 Inst_Max;

layout(location = 3) in float Inst_Layer;
layout(location = 4) in vec3 Inst_Col;

out Vert_UI
{
	vec2	Min;
	vec2	Max;
	vec2	Pos;
	vec3	Col;
} vs_out;



void main()
{
	vec2 main_pos = Main_Pos;
	main_pos.y = -main_pos.y;

	vec2 Center = (Inst_Max + Inst_Min) / 2;
	vec2 SizeHalf = (Inst_Max - Inst_Min) / 2;
	vec2 pos = (main_pos * SizeHalf) + Center;
	vec2 pos_normal = ((pos / ViewPortSizeRatio.Size) * 2) - 1;
	pos_normal.y = -pos_normal.y;

	gl_Position = vec4(pos_normal, Inst_Layer, 1);

	vs_out.Min = Inst_Min;
	vs_out.Max = Inst_Max;
	vs_out.Pos = pos;

	vs_out.Col = Inst_Col;
}
