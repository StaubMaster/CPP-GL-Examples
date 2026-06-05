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
	vec2 BoxSize = Box_Max - Box_Min;

	vec2 pos_pixel = (Pos * BoxSize) + Box_Min;
	vec2 pos_normal = ((pos_pixel / DisplaySize.Buffer.Full) * 2) - 1;

	gl_Position = vec4(pos_normal, 0, 1);
	vs_out.Col = Col;
}
