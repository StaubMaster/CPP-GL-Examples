#version 330



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



layout(location = 0) in vec2 Box_Min;
layout(location = 1) in vec2 Box_Max;

layout(location = 2) in vec2 Pos;
layout(location = 3) in vec4 Col;

out Vert_UI_Graph
{
	vec4	Col;
} vs_out;



void main()
{
	vec2 BoxCenter = (Box_Max + Box_Min) / 2;
	vec2 BoxSizeHalf = (Box_Max - Box_Min) / 2;

	vec2 pos = Pos;
	pos = vec2(+pos.x, -pos.y);
	pos = (pos * BoxSizeHalf) + BoxCenter;
	pos = ((pos / DisplaySize.Buffer.Full) * 2) - 1;
	pos = vec2(+pos.x, -pos.y);

	gl_Position = vec4(pos, 0, 1);
	vs_out.Col = Col;
}
