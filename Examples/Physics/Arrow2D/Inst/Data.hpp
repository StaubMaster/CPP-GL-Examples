#ifndef  ARROW_2D_INST_DATA_HPP
# define ARROW_2D_INST_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/ColorF4.hpp"
# include "ValueType/Line2D.hpp"

namespace Arrow2D
{
namespace Inst
{
struct Data
{
	Point2D		Pos0;
	Point2D		Pos1;
	float		Size;
	ColorF4		Col;
	Data();
	Data(Point2D pos0, Point2D pos1);
	Data(Point2D pos0, Point2D pos1, float size);
	Data(Point2D pos0, Point2D pos1, float size, ColorF4 col);
	Data(Line2D line, float size, ColorF4 col);
};
};
};

#endif