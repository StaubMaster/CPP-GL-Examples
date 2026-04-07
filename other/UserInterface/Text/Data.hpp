#ifndef  UI_TEXT_DATA
# define UI_TEXT_DATA

# include "ValueType/_Include.hpp"

namespace UI
{

namespace Text
{

struct Main_Data
{
	Point2D Pos;

	Main_Data();
	Main_Data(Point2D pos);
};

struct Inst_Data
{
	Point2D Pos;
	AxisBox2D Pallet;
	AxisBox2D Bound;

	Inst_Data();
	Inst_Data(Point2D pos, AxisBox2D pallet);
};

};

};

#endif