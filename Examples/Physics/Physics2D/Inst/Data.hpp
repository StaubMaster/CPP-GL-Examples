#ifndef  PHYSICS_2D_INST_DATA_HPP
# define PHYSICS_2D_INST_DATA_HPP

# include "ValueType/Point2D.hpp"

namespace Physics2D
{
namespace Inst
{
struct Data
{
	Point2D		Pos;
	Point2D		Vel;
	Data();
	Data(Point2D pos);
	Data(Point2D pos, Point2D vel);
};
};
};

#endif