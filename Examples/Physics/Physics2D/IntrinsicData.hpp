#ifndef  PHYSICS_2D_INTRINSIC_DATA_HPP
# define PHYSICS_2D_INTRINSIC_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/Angle2D.hpp"
# include "ValueType/Matrix3x3.hpp"

namespace PolyGon { class Object; }

namespace Physics2D
{
struct IntrinsicData
{
	float		Mass;
	float		Area;
	float		Density;
	Point2D		CenterOfMass;
	float		MomentOfInertia;

	float		BoxCMomentOfInertia;
	float		BoxWMomentOfInertia;
	float		BoxHMomentOfInertia;

	void Calculate_Area(const PolyGon::Object & polygon);
	void Calculate_CenterOfMass(const PolyGon::Object & polygon);
	void Calculate_MomentOfInertia(const PolyGon::Object & polygon);

	void Calculate(const PolyGon::Object & polygon);
};
};

#include <iosfwd>
std::ostream & operator<<(std::ostream & s, const Physics2D::IntrinsicData & data);

#endif