#ifndef  PHYSICS_2D_EXTRINSIC_DATA_HPP
# define PHYSICS_2D_EXTRINSIC_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/Angle2D.hpp"
# include "ValueType/Matrix3x3.hpp"

namespace Physics2D
{
struct ExtrinsicData
{
	float	LinVel;
	float	LinMom;

	float	AngVel;
	float	AngMom;
};
};

#endif