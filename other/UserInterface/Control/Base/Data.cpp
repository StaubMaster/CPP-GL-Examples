#include "Data.hpp"



UI::Control::Main_Data::Main_Data()
{ }
UI::Control::Main_Data::Main_Data(VectorF2 pos) :
	Pos(pos)
{ }



UI::Control::Inst_Data::Inst_Data()
{ }
UI::Control::Inst_Data::Inst_Data(VectorF2 min, VectorF2 max, float layer, ColorF4 col) :
	Min(min),
	Max(max),
	Layer(layer),
	Col(col)
{ }
