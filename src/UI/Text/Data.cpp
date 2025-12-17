#include "Data.hpp"



UI::Text::Main_Data::Main_Data() {}
UI::Text::Main_Data::Main_Data(Point2D pos) :
	Pos(pos)
{ }



UI::Text::Inst_Data::Inst_Data() { }
UI::Text::Inst_Data::Inst_Data(Point2D pos, AxisBox2D pallet) :
	Pos(pos),
	Pallet(pallet)
{ }
