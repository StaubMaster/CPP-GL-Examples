#include "Physics2D/ExtrinsicData.hpp"
#include "Physics2D/IntrinsicData.hpp"



void Physics2D::ExtrinsicData::Calculate(const IntrinsicData & int_data, Trans2D vel)
{
	LinVel = vel.Pos.length();
	LinMom = LinVel * (int_data.Mass);

	AngVel = vel.Rot.Ang.ToRadians();
	AngMom = AngVel * (int_data.MomentOfInertia);
}



#include <iostream>
#include "DataShow.hpp"
std::ostream & operator<<(std::ostream & s, const Physics2D::ExtrinsicData & data)
{
	s << "Extrinsic:\n";
	s << "Linear Velocity  : " << data.LinVel << " dm/s\n";
	s << "Linear Momentum  : " << data.LinMom << " kg*dm/s\n";
	s << "Angular Velocity : " << data.AngVel << " dm/dm*s\n";
	s << "Angular Momentum : " << data.AngMom << " kg*dm^2/s\n";
	s << '\n';
	return s;
}
