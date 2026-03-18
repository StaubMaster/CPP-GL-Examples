#ifndef  PHYSICS_2D_INTRINSIC_DATA_HPP
# define PHYSICS_2D_INTRINSIC_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/Angle2D.hpp"
# include "ValueType/Matrix3x3.hpp"

namespace Physics2D
{
struct IntrinsicData
{
	float		Mass;
	float		Area;
	Point2D		CenterOfMass;
	float		MomentOfInertia;
	Matrix3x3	InertiaTensor;
};
};

#endif