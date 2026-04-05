#ifndef  PHYSICS_2D_INTRINSIC_DATA_HPP
# define PHYSICS_2D_INTRINSIC_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/Matrix3x3.hpp"

class PolyGon;

namespace Physics2D
{
struct IntrinsicData
{
	float		Mass;
	float		Area;
	float		Density;
	Point2D		CenterOfMass;
	float		MomentOfInertia;
	float		Restitution;

	float		BoxCMomentOfInertia;
	float		BoxWMomentOfInertia;
	float		BoxHMomentOfInertia;

	void Calculate_Area(const PolyGon & polygon);
	void Calculate_CenterOfMass(const PolyGon & polygon);
	void Calculate_MomentOfInertia(const PolyGon & polygon);

	void Calculate(const PolyGon & polygon);
};
};

#include <iosfwd>
std::ostream & operator<<(std::ostream & s, const Physics2D::IntrinsicData & data);

#endif