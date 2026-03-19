#ifndef  PHYSICS_2D_EXTRINSIC_DATA_HPP
# define PHYSICS_2D_EXTRINSIC_DATA_HPP

# include "ValueType/Trans2D.hpp"

namespace Physics2D
{
struct IntrinsicData;
struct ExtrinsicData
{
	float	LinVel;
	float	LinMom;

	float	AngVel;
	float	AngMom;

	void Calculate(const IntrinsicData & int_data, Trans2D vel);
};
};

#include <iosfwd>
std::ostream & operator<<(std::ostream & s, const Physics2D::ExtrinsicData & data);

#endif