#ifndef  PHYSICS_2D_EXTRINSIC_DATA_HPP
# define PHYSICS_2D_EXTRINSIC_DATA_HPP

# include "ValueType/Point2D.hpp"
# include "ValueType/Angle.hpp"
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

	void Zero();

	void Change(Point2D change);
	void Change(Angle change);

	void Update(float timeDelta);
	void Update(const IntrinsicData & int_data);
};
};

#include <iosfwd>
std::ostream & operator<<(std::ostream & s, const Physics2D::ExtrinsicData & data);

#endif