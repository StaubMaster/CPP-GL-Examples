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
} Pallets; // FontPallets



// Texts
const uint TextLimit = 64u;
struct TextData
{
	BoxF2	Bound;
	vec4	Color;
	vec2	CharSize;
};
layout(std140) uniform ITexts
{
	TextData	Array[TextLimit];
} Texts;



layout(location = 0) in vec2 Main_Pos;	//	square in range [ -1 , +1 ]

layout(location = 1) in vec2 Inst_Text_Pos;
layout(location = 2) in uint Inst_Char_Idx;
layout(location = 3) in uint Inst_Text_Idx;



out UI_Text
{
	vec2	PalletPos;
	BoxF2	Bound;
	vec4	Color;
} vs_out;



// NormalAbs is [ 0 ; 1 ]
// NormalRel is [ -1 ; +1 ]
// make Converter functions
vec2 NormalRelToAbs(vec2 pos) { return (pos + 1) / 2; }
vec2 NormalAbsToRel(vec2 pos) { return (pos * 2) - 1; }

// fix y invertion

// clean this code
void main()
{
	TextData text_data = Texts.Array[Inst_Text_Idx];

	vec2 main_pos = Main_Pos;
	main_pos.y = -main_pos.y;

	vec2 Center = Inst_Text_Pos;
	vec2 SizeHalf = text_data.CharSize / 2;
	vec2 pos = (main_pos * SizeHalf) + Center;
	vec2 pos_normal = NormalAbsToRel(pos / DisplaySize.Buffer.Full);
	pos_normal.y = -pos_normal.y;

	gl_Position = vec4(pos_normal, 0.01, 1);

	vec2 pallet_t0 = NormalRelToAbs(main_pos);
	vec2 pallet_t1 = vec2(1, 1) - pallet_t0;

	BoxF2 pallet_box = Pallets.Array[Inst_Char_Idx];
	vs_out.PalletPos = (pallet_box.Min * pallet_t1) + (pallet_box.Max * pallet_t0);

	BoxF2 bound = text_data.Bound;

	vs_out.Bound.Min.x = bound.Min.x;
	vs_out.Bound.Min.y = DisplaySize.Buffer.Full.y - bound.Max.y;
	vs_out.Bound.Max.x = bound.Max.x;
	vs_out.Bound.Max.y = DisplaySize.Buffer.Full.y - bound.Min.y;

	vs_out.Color = text_data.Color;
}
