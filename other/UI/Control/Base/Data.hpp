#ifndef  UI_CONTROL_DATA_HPP
# define UI_CONTROL_DATA_HPP

#include "DataInclude.hpp"



namespace UI
{

namespace Control
{

struct Main_Data
{
	Point2D	Pos;

	Main_Data();
	Main_Data(Point2D pos);
};
struct Inst_Data
{
	Point2D	Min;
	Point2D	Max;
	float	Layer;
	ColorF4	Col;

	Inst_Data();
	Inst_Data(Point2D min, Point2D max, float layer, ColorF4 col);
};

};

};

#endif