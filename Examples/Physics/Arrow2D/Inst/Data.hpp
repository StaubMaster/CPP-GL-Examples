#ifndef  ARROW_2D_INST_DATA_HPP
# define ARROW_2D_INST_DATA_HPP

# include "ValueType/Point2D.hpp"

namespace Arrow2D
{
namespace Inst
{
struct Data
{
	Point2D		Pos;
	Point2D		Dir;
	float		Size;
	Data();
	Data(Point2D pos, Point2D dir);
	Data(Point2D pos, Point2D dir, float size);
};
};
};

#endif