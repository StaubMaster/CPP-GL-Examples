#version 330



struct BoxF2
{
	vec2	Min;
	vec2	Max;
};
vec2 center(BoxF2 box)
{
	return (box.Max + box.Min) / 2;
}
vec2 size(BoxF2 box)
{
	return (box.Max - box.Min);
}

struct PixelSize
{
	vec2	Full;
	vec2	Half;
};
struct sDisplaySize
{
	vec2		Ratio;
	PixelSize	Window;
	PixelSize	Buffer;
};

uniform sDisplaySize DisplaySize;



layout(location = 0) in vec2	Main_Pos;	//	square in range [ -1 , +1 ]

layout(location = 1) in vec2	Inst_Box_Min;
layout(location = 2) in vec2	Inst_Box_Max;
layout(location = 3) in float	Inst_Layer;
layout(location = 4) in vec4	Inst_Color;
layout(location = 5) in vec2	Inst_Bound_Min;
layout(location = 6) in vec2	Inst_Bound_Max;

out Vert_UI
{
	vec2	Pos;
	BoxF2	Box;
	vec4	Color;
	BoxF2	Bound;
} vs_out;



void main()
{
	BoxF2 Box = BoxF2(Inst_Box_Min, Inst_Box_Max);
	vec2 Box_Center = (Inst_Box_Max + Inst_Box_Min) / 2;
	vec2 Box_SizeHalf = (Inst_Box_Max - Inst_Box_Min) / 2;

	vs_out.Pos = (Main_Pos * Box_SizeHalf) + Box_Center;

	vec2 pos = (vs_out.Pos - DisplaySize.Buffer.Half) / DisplaySize.Buffer.Half;
	pos = vec2(+pos.x, -pos.y);
	gl_Position = vec4(pos, Inst_Layer, 1);

	vs_out.Box.Min = Inst_Box_Min;
	vs_out.Box.Max = Inst_Box_Max;
	vs_out.Color = Inst_Color;
	vs_out.Bound.Min = Inst_Bound_Min;
	vs_out.Bound.Max = Inst_Bound_Max;

//	vec2 col = (Main_Pos + 1.0) / 2.0;
//	vs_out.Color = vec4(col.x, 0, col.y, 1);
}
