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
layout(std140) uniform IPallets
{
	BoxF2	Array[PalletLimit];
} Pallets;



// Texts
const uint TextLimit = 64u;
struct TextData
{
	BoxF2	Bound;
	vec4	Color;
};
layout(std140) uniform ITexts
{
	TextData	Array[TextLimit];
} Texts;



//const vec2 CharacterSize = vec2(32, 32);
//const vec2 CharacterSize = vec2(20, 20);
const vec2 CharacterSize = vec2(12, 12);

/* Character Size
global ?
per Text ?
pre Char ?
*/



layout(location = 0) in vec2 Main_Pos;	//	square in range [ -1 , +1 ]

layout(location = 1) in vec2 Inst_Pos;
layout(location = 2) in uint Inst_Pallet_Idx;
layout(location = 3) in uint Inst_Text_Idx;



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

	BoxF2 pallet_box = Pallets.Array[Inst_Pallet_Idx];
	vs_out.PalletPos = (pallet_box.Min * pallet_t0) + (pallet_box.Max * pallet_t1);

	BoxF2 bound = Texts.Array[Inst_Text_Idx].Bound;

	vs_out.BoundMin.x = bound.Min.x;
	vs_out.BoundMin.y = DisplaySize.Buffer.Full.y - bound.Max.y;
	vs_out.BoundMax.x = bound.Max.x;
	vs_out.BoundMax.y = DisplaySize.Buffer.Full.y - bound.Min.y;

	vs_out.Color = Texts.Array[Inst_Text_Idx].Color;
}
