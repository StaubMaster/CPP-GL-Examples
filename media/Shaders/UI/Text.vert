#version 330



struct SizeRatio2D
{
	vec2 Size;
	vec2 Ratio;
};

uniform SizeRatio2D ViewPortSizeRatio;

const vec2 TexturePalletCount = vec2(16, 8);
const vec2 PalletSize = vec2(25, 25);



layout(location = 0) in vec2 Main_Pos;	//	square in range [ -1 , +1 ]

layout(location = 1) in vec2 Inst_Pos;
layout(location = 2) in vec2 Inst_Pallet;

out UI_Text
{
	vec2	PalletPos;
} vs_out;



void main()
{
	vec2 main_pos = Main_Pos;
	main_pos.y = -main_pos.y;

	vec2 Center = Inst_Pos;
	vec2 SizeHalf = PalletSize / 2;
	vec2 pos = (main_pos * SizeHalf) + Center;
	vec2 pos_normal = ((pos / ViewPortSizeRatio.Size) * 2) - 1;
	pos_normal.y = -pos_normal.y;

	gl_Position = vec4(pos_normal, 0.01, 1);

	vec2 pallet_pos = vec2(+Main_Pos.x, -Main_Pos.y);
	pallet_pos = ((pallet_pos + vec2(1, 1)) / 2);
	pallet_pos = Inst_Pallet + pallet_pos;
	pallet_pos = (pallet_pos / TexturePalletCount);
	vs_out.PalletPos = pallet_pos;
}
