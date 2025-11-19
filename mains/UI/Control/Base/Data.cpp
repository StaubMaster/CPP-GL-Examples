#include "Data.hpp"



Control::Main_Data::Main_Data() { }
Control::Main_Data::Main_Data(Point2D pos) :
	Pos(pos)
{ }



Control::Inst_Data::Inst_Data() { }
Control::Inst_Data::Inst_Data(Point2D min, Point2D max, float layer, Color col) :
	Min(min),
	Max(max),
	Layer(layer),
	Col(col)
{ }
