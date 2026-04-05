#ifndef  ARROW_2D_MAIN_DATA_HPP
# define ARROW_2D_MAIN_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/Point3D.hpp"

namespace Arrow2D
{
namespace Main
{
struct Data
{
	Point2D		Pos;
	Point3D		Tex;
	Data();
	Data(Point2D pos);
	Data(Point2D pos, Point3D tex);
};
};
};

#endif