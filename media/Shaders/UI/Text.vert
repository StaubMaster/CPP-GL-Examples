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



struct BoxF2
{
	vec2	Min;
	vec2	Max;
};



// Pallets
const uint PalletLimit = 128u;
uniform vec2 PalletArrayMin[PalletLimit];
uniform vec2 PalletArrayMax[PalletLimit];
/*layout(std140) uniform IPallets
{
	//uint	PalletCount;
	BoxF2	PalletArray[PalletLimit];
} Pallets;*/



// Texts
const uint TextLimit = 64u;
uniform vec2 TextBoundArrayMin[TextLimit];
uniform vec2 TextBoundArrayMax[TextLimit];
uniform vec4 TextColorArray[TextLimit];
struct TextData
{
	BoxF2	Bound;
	vec4	Color;
	//vec2	CharacterSize;
};
/*layout(std140) uniform ITexts
{
	//uint		TextCount;
	TextData	TextArray[TextLimit];
} Texts;*/



//const vec2 CharacterSize = vec2(32, 32);
const vec2 CharacterSize = vec2(20, 20);



layout(location = 0) in vec2 Main_Pos;	//	square in range [ -1 , +1 ]

layout(location = 1) in vec2 Inst_Pos;
layout(location = 2) in uint Inst_PalletIdx;
layout(location = 3) in uint Inst_TextIdx;



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
	vec2 SizeHalf = CharacterSize / 2;
	vec2 pos = (main_pos * SizeHalf) + Center;
	vec2 pos_normal = ((pos / DisplaySize.Buffer.Full) * 2) - 1;
	pos_normal.y = -pos_normal.y;

	gl_Position = vec4(pos_normal, 0.01, 1);

	vec2 pallet_t0 = ((vec2(-Main_Pos.x, +Main_Pos.y) + vec2(1, 1)) / 2);
	vec2 pallet_t1 = vec2(1, 1) - pallet_t0;
	vs_out.PalletPos = (PalletArrayMin[Inst_PalletIdx] * pallet_t0) + (PalletArrayMax[Inst_PalletIdx] * pallet_t1);

	vec2 bound_min = TextBoundArrayMin[Inst_TextIdx];
	vec2 bound_max = TextBoundArrayMax[Inst_TextIdx];

	vs_out.BoundMin.x = bound_min.x;
	vs_out.BoundMin.y = DisplaySize.Buffer.Full.y - bound_max.y;
	vs_out.BoundMax.x = bound_max.x;
	vs_out.BoundMax.y = DisplaySize.Buffer.Full.y - bound_min.y;

	vs_out.Color = TextColorArray[Inst_TextIdx];
}
