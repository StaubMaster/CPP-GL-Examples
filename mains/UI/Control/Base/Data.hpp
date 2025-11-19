#ifndef  CONTROL_DATA_HPP
# define CONTROL_DATA_HPP

#include "DataInclude.hpp"



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
	Color Col;

	Inst_Data();
	Inst_Data(Point2D min, Point2D max, float layer, Color col);
};
};

#endif