#version 330



struct DisplaySize
{
	vec2 WindowSize;
	vec2 BufferSize;
	vec2 Ratio;
};

uniform DisplaySize WindowSize;

const vec2 TexturePalletCount = vec2(16, 8);
const vec2 PalletSize = vec2(20, 20);



layout(location = 0) in vec2 Main_Pos;	//	square in range [ -1 , +1 ]

layout(location = 1) in vec2 Inst_Pos;
layout(location = 2) in vec2 Inst_Pallet;

layout(location = 3) in vec2 Inst_BoundMin;
layout(location = 4) in vec2 Inst_BoundMax;

out UI_Text
{
	vec2	PalletPos;
	vec2	BoundMin;
	vec2	BoundMax;
} vs_out;



void main()
{
	vec2 main_pos = Main_Pos;
	main_pos.y = -main_pos.y;

	vec2 Center = Inst_Pos;
	vec2 SizeHalf = PalletSize / 2;
	vec2 pos = (main_pos * SizeHalf) + Center;
	vec2 pos_normal = ((pos / WindowSize.BufferSize) * 2) - 1;
	pos_normal.y = -pos_normal.y;

	gl_Position = vec4(pos_normal, 0.01, 1);

	vec2 pallet_pos = vec2(+Main_Pos.x, -Main_Pos.y);
	pallet_pos = ((pallet_pos + vec2(1, 1)) / 2);
	pallet_pos = Inst_Pallet + pallet_pos;
	pallet_pos = (pallet_pos / TexturePalletCount);
	vs_out.PalletPos = pallet_pos;

	vs_out.BoundMin.x = Inst_BoundMin.x;
	vs_out.BoundMin.y = WindowSize.BufferSize.y - Inst_BoundMax.y;
	vs_out.BoundMax.x = Inst_BoundMax.x;
	vs_out.BoundMax.y = WindowSize.BufferSize.y - Inst_BoundMin.y;
}
