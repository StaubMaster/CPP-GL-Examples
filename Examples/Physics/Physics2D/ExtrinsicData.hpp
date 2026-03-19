#ifndef  PHYSICS_2D_EXTRINSIC_DATA_HPP
# define PHYSICS_2D_EXTRINSIC_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/Angle2D.hpp"
# include "ValueType/Trans2D.hpp"

namespace Physics2D
{
struct IntrinsicData;
struct ExtrinsicData
{
	Trans2D	Now;
	Trans2D	Vel;
	Trans2D	Acl;

	float	LinVel;
	float	LinMom;
	float	LinAcl;

	float	AngVel;
	float	AngMom;
	float	AngAcl;

	void Calculate(const IntrinsicData & int_data);

	void Update(float timeDelta);
};
};

#include <iosfwd>
std::ostream & operator<<(std::ostream & s, const Physics2D::ExtrinsicData & data);

#endif