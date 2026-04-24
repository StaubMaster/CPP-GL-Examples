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

//const vec2 PalletSize = vec2(32, 32);
const vec2 PalletSize = vec2(20, 20);



layout(location = 0) in vec2 Main_Pos;	//	square in range [ -1 , +1 ]

layout(location = 1) in vec2 Inst_Pos;

layout(location = 2) in vec2 Inst_PalletMin;
layout(location = 3) in vec2 Inst_PalletMax;

layout(location = 4) in vec2 Inst_BoundMin;
layout(location = 5) in vec2 Inst_BoundMax;

layout(location = 6) in vec4 Inst_Color;



out UI_Text
{
	vec2	PalletPos;
	vec2	BoundMin;
	vec2	BoundMax;
	vec4	Color;
} vs_out;



void main()
{
	vec2 main_pos = Main_Pos;
	main_pos.y = -main_pos.y;

	vec2 Center = Inst_Pos;
	vec2 SizeHalf = PalletSize / 2;
	vec2 pos = (main_pos * SizeHalf) + Center;
	vec2 pos_normal = ((pos / DisplaySize.Buffer.Full) * 2) - 1;
	pos_normal.y = -pos_normal.y;

	gl_Position = vec4(pos_normal, 0.01, 1);

	vec2 pallet_t0 = ((vec2(-Main_Pos.x, +Main_Pos.y) + vec2(1, 1)) / 2);
	vec2 pallet_t1 = vec2(1, 1) - pallet_t0;
	vs_out.PalletPos = (Inst_PalletMin * pallet_t0) + (Inst_PalletMax * pallet_t1);

	//vs_out.BoundMin = Inst_BoundMin;
	//vs_out.BoundMax = Inst_BoundMax;

	vs_out.BoundMin.x = Inst_BoundMin.x;
	vs_out.BoundMin.y = DisplaySize.Buffer.Full.y - Inst_BoundMax.y;
	vs_out.BoundMax.x = Inst_BoundMax.x;
	vs_out.BoundMax.y = DisplaySize.Buffer.Full.y - Inst_BoundMin.y;

	vs_out.Color = Inst_Color;
}
