#ifndef  UI_TEXT_DATA
# define UI_TEXT_DATA

# include "ValueType/_Include.hpp"

namespace UI
{

namespace Text
{

struct Main_Data
{
	VectorF2	Pos;

	Main_Data();
	Main_Data(VectorF2 pos);
};

struct Inst_Data
{
	VectorF2	Pos;
	BoxF2		Pallet;
	BoxF2		Bound;
	ColorF4		Color;

	Inst_Data();
	Inst_Data(VectorF2 pos, BoxF2 pallet);
	Inst_Data(VectorF2 pos, BoxF2 pallet, ColorF4 color);
};

};

};

#endif