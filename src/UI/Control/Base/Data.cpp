#include "Data.hpp"



UI::Control::Main_Data::Main_Data()
{ }
UI::Control::Main_Data::Main_Data(Point2D pos) :
	Pos(pos)
{ }



UI::Control::Inst_Data::Inst_Data()
{ }
UI::Control::Inst_Data::Inst_Data(Point2D min, Point2D max, float layer, Color col) :
	Min(min),
	Max(max),
	Layer(layer),
	Col(col)
{ }
