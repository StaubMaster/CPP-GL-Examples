#include "Data.hpp"



UI::Text::Main_Data::Main_Data() {}
UI::Text::Main_Data::Main_Data(VectorF2 pos)
	: Pos(pos)
{ }



UI::Text::Inst_Data::Inst_Data() { }
UI::Text::Inst_Data::Inst_Data(VectorF2 pos, BoxF2 pallet)
	: Pos(pos)
	, Pallet(pallet)
{ }
UI::Text::Inst_Data::Inst_Data(VectorF2 pos, BoxF2 pallet, ColorF4 color)
	: Pos(pos)
	, Pallet(pallet)
	, Color(color)
{ }
