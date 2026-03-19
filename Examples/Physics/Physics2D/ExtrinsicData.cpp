#include "Physics2D/ExtrinsicData.hpp"
#include "Physics2D/IntrinsicData.hpp"



void Physics2D::ExtrinsicData::Calculate(const IntrinsicData & int_data)
{
	LinVel = Vel.Pos.length();
	LinMom = LinVel * (int_data.Mass);
	LinAcl = Acl.Pos.length();

	AngVel = Vel.Rot.Ang.ToRadians();
	AngMom = AngVel * (int_data.MomentOfInertia);
	AngAcl = Acl.Rot.Ang.ToRadians();
}

void Physics2D::ExtrinsicData::Update(float timeDelta)
{
	Vel.Pos += Acl.Pos * timeDelta;
	Vel.Rot += Acl.Rot * timeDelta;

	Now.Pos += Vel.Pos * timeDelta;
	Now.Rot += Vel.Rot * timeDelta;

	Acl.Pos = Point2D();
	Acl.Rot = Angle2D();
}



#include <iostream>
#include "DataShow.hpp"
std::ostream & operator<<(std::ostream & s, const Physics2D::ExtrinsicData & data)
{
	s << "Extrinsic:\n";

//	s << "Position Now : " << data.PosNow << " dm\n";
//	s << "Position Vel : " << data.PosVel << " dm/s\n";
//	s << "Position Acl : " << data.PosAcl << " dm/s^2\n";

	s << "Linear Velocity     : " << data.LinVel << " dm/s\n";
	s << "Linear Momentum     : " << data.LinMom << " kg*dm/s\n";
	s << "Linear Acceleration : " << data.LinAcl << " dm/s^2\n";

//	s << "Rotation Now : " << data.RotNow << " dm/dm\n";
//	s << "Rotation Vel : " << data.RotVel << " dm/dm*s\n";
//	s << "Rotation Acl : " << data.RotAcl << " dm/dm*s^2\n";

	s << "Angular Velocity     : " << data.AngVel << " dm/dm*s\n";
	s << "Angular Momentum     : " << data.AngMom << " kg*dm^2/s\n";
	s << "Angular Acceleration : " << data.AngAcl << " kg*dm^2/s^2\n";

	s << '\n';
	return s;
}
