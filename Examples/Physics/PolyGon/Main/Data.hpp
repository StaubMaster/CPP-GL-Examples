#ifndef  PHYSICS_2D_MAIN_DATA_HPP
# define PHYSICS_2D_MAIN_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/ColorF4.hpp"

namespace Physics2D
{
namespace Main
{
struct Data
{
	Point2D		Pos;
	ColorF4		Col;
	Data();
	Data(Point2D pos);
	Data(Point2D pos, ColorF4 col);
};
};
};

#endif