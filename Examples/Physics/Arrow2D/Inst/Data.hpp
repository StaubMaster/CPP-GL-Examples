#ifndef  ARROW_2D_INST_DATA_HPP
# define ARROW_2D_INST_DATA_HPP

# include "ValueType/Point2D.hpp"

namespace Arrow2D
{
namespace Inst
{
struct Data
{
	Point2D		Pos0;
	Point2D		Pos1;
	float		Size;
	Data();
	Data(Point2D pos0, Point2D pos1);
	Data(Point2D pos0, Point2D pos1, float size);
};
};
};

#endif