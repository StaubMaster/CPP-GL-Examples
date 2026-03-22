#include "Physics2D/Collision.hpp"
#include "Physics2D/Collision/ObjectProjection.hpp"
#include "PolyGon/Data.hpp"

#include "ValueType/Point3D.hpp"
#include "ValueType/Trans2D.hpp"

#include "DataShow.hpp"

#include "IntrinsicData.hpp"
#include "ExtrinsicData.hpp"

#include <cmath>





Physics2D::Collision::ContactData::~ContactData() { }
Physics2D::Collision::ContactData::ContactData()
	: Valid(false)
//	, Contact0()
//	, Contact1()
	, Undex0(0xFFFFFFFF)
	, Undex1(0xFFFFFFFF)
	, Normal()
	, Position()
//	, Velocity()
	, Distance(INFINITY)
//	, Contact0Udx(0xFFFFFFFF)
//	, Contact1Udx(0xFFFFFFFF)
{ }

Physics2D::Collision::ContactData::ContactData(const ContactData & other)
	: Valid(other.Valid)
	//, Contact0(other.Contact0)
	//, Contact1(other.Contact1)
	, Undex0(other.Undex0)
	, Undex1(other.Undex1)
	, Normal(other.Normal)
	, Position(other.Position)
	//, Velocity(other.Velocity)
	, Distance(other.Distance)
	//, Contact0Udx(other.Contact0Udx)
	//, Contact1Udx(other.Contact1Udx)
{ }
Physics2D::Collision::ContactData & Physics2D::Collision::ContactData::operator=(const ContactData & other)
{
	Valid = other.Valid;
	Undex0 = other.Undex0;
	Undex1 = other.Undex1;
	Normal = other.Normal;
	Position = other.Position;
	Distance = other.Distance;
	//Contact0Udx = other.Contact0Udx;
	//Contact1Udx = other.Contact1Udx;
	return *this;
}



bool Physics2D::Collision::ContactData::Compare(const ContactData & other) const
{
	if (!other.Valid) { return false; }
	if (!Valid) { return true; }
	return (fabs(other.Distance) < fabs(Distance));
}
void Physics2D::Collision::ContactData::Consider(const ContactData & other)
{
	if (Compare(other))
	{
		*this = other;
	}
}

Point2D Physics2D::Collision::ContactData::CalculateNormal(const Object & obj, unsigned int idx)
{
	Point2D p0;
	Point2D p1;
	if (idx == 0)
	{
		p0 = obj.AbsolutePositionOfIndex(obj.CornerCount() - 1);
		p1 = obj.AbsolutePositionOfIndex(idx - 0);
	}
	else
	{
		p0 = obj.AbsolutePositionOfIndex(idx - 1);
		p1 = obj.AbsolutePositionOfIndex(idx - 0);
	}
	return (p1 - p0).perpendicular0().normalize();
}



Physics2D::Collision::ContactData Physics2D::Collision::ContactData::CheckContact(
	const Object & obj0,
	const Object & obj1,
	Point2D normal,
	float timeDelta
)
{
	(void)timeDelta;
	ContactData data;
	Collision::ObjectProjectionOverlap overlap = Collision::ObjectProjectionOverlap::Overlap(normal, obj0, obj1);
	if (overlap.Valid)
	{
		data.Normal = normal;
		data.Distance = overlap.Distance;
		data.Undex0 = overlap.Undex0;
		data.Undex1 = overlap.Undex1;
		data.Valid = true;
	}
	return data;
}

#include "Arrow2D/Object.hpp"
/* multiple Contacts ?
	resolve all ?
	remember all and split Forces ?
*/
Physics2D::Collision::ContactData Physics2D::Collision::ContactData::CheckContact(
	const Object & obj0,
	const Object & obj1,
	float timeDelta
)
{
	(void)timeDelta;

	ContactData	ret;
	ContactData	data;
	ContactData	temp;
	Point2D		n;

	for (unsigned int i = 0; i < obj0.CornerCount(); i++)
	{
		n = CalculateNormal(obj0, i);
		temp = CheckContact(obj0, obj1, n, timeDelta);
		if (!temp.Valid) { return ret; }
		temp.Position = obj1.AbsolutePositionOfIndex(temp.Undex1);
		data.Consider(temp);
	}

	for (unsigned int i = 0; i < obj1.CornerCount(); i++)
	{
		n = CalculateNormal(obj1, i);
		temp = CheckContact(obj0, obj1, n, timeDelta);
		if (!temp.Valid) { return ret; }
		temp.Position = obj0.AbsolutePositionOfIndex(temp.Undex0);
		data.Consider(temp);
	}

	ret = data;
	return ret;
}

Physics2D::Collision::ContactData::ResolveData Physics2D::Collision::ContactData::Resolve(
	Object & obj0,
	Object & obj1,
	float timeDelta
)
{
	(void)timeDelta;

	Point2D PosRel0 = obj0.RelativePositionOfIndex(Undex0);
	Point2D PosAbs0 = obj0.AbsolutePositionOf(PosRel0);
	Point2D VelAbs0 = obj0.AbsoluteVelocityOf(PosAbs0);

	Point2D PosRel1 = obj1.RelativePositionOfIndex(Undex1);
	Point2D PosAbs1 = obj1.AbsolutePositionOf(PosRel1);
	Point2D VelAbs1 = obj1.AbsoluteVelocityOf(PosAbs1);

	Point2D Velocity = VelAbs1 - VelAbs0;

	{
		Arrow2D::Object arrows(4);
		arrows[0] = Arrow2D::Inst::Data(ColorF4(0.5f, 0.0f, 0.0f), 16.0f, Line2D(obj0.ExtData.Now.Pos, Position));
		arrows[1] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.0f, 0.5f), 16.0f, Line2D(obj1.ExtData.Now.Pos, Position));
		arrows[2] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.5f), 16.0f, Ray2D(Position, obj0.AbsoluteVelocityOf(Position)));
		arrows[3] = Arrow2D::Inst::Data(ColorF4(0.5f, 0.5f, 1.0f), 16.0f, Ray2D(Position, obj1.AbsoluteVelocityOf(Position)));
	}

	// IsStatic assumes and infinite Mass to Inverse Mass is 0
	float MassInverse0 = 0.0f;
	float MassInverse1 = 0.0f;
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.IntData.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.IntData.Mass; }
	float MassInverseSum = MassInverse0 + MassInverse1;

	float MomentOfInertiaInverse0 = 0.0f;
	float MomentOfInertiaInverse1 = 0.0f;
	if (!obj0.IsStatic) { MomentOfInertiaInverse0 = 1 / obj0.IntData.MomentOfInertia; }
	if (!obj1.IsStatic) { MomentOfInertiaInverse1 = 1 / obj1.IntData.MomentOfInertia; }

//	Point2D Contact0 = obj0.AbsolutePositionOf(obj0.CornerFromIndex(contact_data.Contact0Udx));
//	Point2D Contact1 = obj1.AbsolutePositionOf(obj1.CornerFromIndex(contact_data.Contact1Udx));

	Point2D RelativeContact0 = Position - obj0.ExtData.Now.Pos;
	Point2D RelativeContact1 = Position - obj1.ExtData.Now.Pos;
	//Point2D RelativeContact0 = contact_data.Contact0.PosAbs - obj0.ExtData.Now.Pos;
	//Point2D RelativeContact1 = contact_data.Contact1.PosAbs - obj1.ExtData.Now.Pos;

	//contact_data.Velocity = contact_data.Velocity * timeDelta;
	float NormalVelFactor = Point2D::dot(Velocity, Normal);

//	Point3D normal_3D(contact_data.Normal.X, contact_data.Normal.Y, 0);
//	Point3D RelativeContact0_3D(RelativeContact0.X, RelativeContact0.Y, 0);
//	Point3D RelativeContact1_3D(RelativeContact1.X, RelativeContact1.Y, 0);
//
//	Point3D ContactNormal0_3D = Point3D::cross(RelativeContact0_3D, normal_3D);
//	Point3D ContactNormal1_3D = Point3D::cross(RelativeContact1_3D, normal_3D);
//	Point3D ContactPerpendicular0_3D = Point3D::cross(ContactNormal0_3D, RelativeContact0_3D);
//	Point3D ContactPerpendicular1_3D = Point3D::cross(ContactNormal1_3D, RelativeContact1_3D);
//	Point3D ContactPerpendicularSum_3D = ContactPerpendicular0_3D + ContactPerpendicular1_3D;
//
//	float InertiaFactorSum = Point2D::dot(Point2D(ContactPerpendicularSum_3D.X, ContactPerpendicularSum_3D.Y), contact_data.Normal);

	float ContactAxis0 = Point2D::cross(RelativeContact0, Normal);
	float ContactAxis1 = Point2D::cross(RelativeContact1, Normal);
	Point2D ContactMomentOfInertia0 = Point2D::cross(ContactAxis0 * MomentOfInertiaInverse0, RelativeContact0);
	Point2D ContactMomentOfInertia1 = Point2D::cross(ContactAxis1 * MomentOfInertiaInverse1, RelativeContact1);
	Point2D ContactMomentOfInertiaSum = ContactMomentOfInertia0 + ContactMomentOfInertia1;

	float MomentOfInertiaSum = Point2D::dot(ContactMomentOfInertiaSum, Normal);

//	std::cout << "RelativeContact0: " << RelativeContact0 << ' ' << RelativeContact0.length() << '\n';
//	std::cout << "RelativeContact1: " << RelativeContact1 << ' ' << RelativeContact1.length() << '\n';
//	std::cout << "ContactPerpendicular0: " << ContactPerpendicular0 << ' ' << ContactPerpendicular0.length() << '\n';
//	std::cout << "ContactPerpendicular1: " << ContactPerpendicular1 << ' ' << ContactPerpendicular1.length() << '\n';
//	std::cout << "ContactPerpendicularSum: " << ContactPerpendicularSum << ' ' << ContactPerpendicularSum.length() << '\n';
//	std::cout << '\n';

	std::cout << "IsStatic[0] " << obj0.IsStatic << '\n';
	std::cout << "IsStatic[1] " << obj1.IsStatic << '\n';
	std::cout << "Inverse Linear Mass [0]  : " << (MassInverse0) << '\n';
	std::cout << "Inverse Linear Mass [1]  : " << (MassInverse1) << '\n';
	std::cout << "Inverse Angular Mass [0] : " << (MomentOfInertiaInverse0) << '\n';
	std::cout << "Inverse Angular Mass [1] : " << (MomentOfInertiaInverse1) << '\n';
	std::cout << '\n';

	std::cout << "Contact [0] : \n" << Undex0 << '\n';
	//std::cout << "Position Relative : " << contact_data.Contact0.PosRel << '\n';
	//std::cout << "Position Absolute : " << contact_data.Contact0.PosAbs << '\n';
	////std::cout << "Velocity Relative : " << contact_data.Contact0.VelRel << '\n';
	//std::cout << "Velocity Absolute : " << contact_data.Contact0.VelAbs << '\n';
	std::cout << '\n';

	std::cout << "Contact [1] : \n" << Undex1 << '\n';
	//std::cout << "Position Relative : " << contact_data.Contact1.PosRel << '\n';
	//std::cout << "Position Absolute : " << contact_data.Contact1.PosAbs << '\n';
	////std::cout << "Velocity Relative : " << contact_data.Contact1.VelRel << '\n';
	//std::cout << "Velocity Absolute : " << contact_data.Contact1.VelAbs << '\n';
	std::cout << '\n';

	//std::cout << "Contact Position : " << contact_data.Position << " dm\n";
	//std::cout << "Contact Velocity : " << contact_data.Velocity << " dm/s\n";
	std::cout << "Contact Normal   : " << Normal << ' ' << Normal.length() << '\n';
	std::cout << '\n';

	std::cout << "NormalVelFactor  : " << NormalVelFactor << '\n';
	std::cout << "Contact Axis [0] : " << ContactAxis0 << '\n';
	std::cout << "Contact Axis [1] : " << ContactAxis1 << '\n';
	std::cout << "Contact Moment of Inertia [0] : " << ContactMomentOfInertia0 << '\n';
	std::cout << "Contact Moment of Inertia [1] : " << ContactMomentOfInertia1 << '\n';
	std::cout << "Contact Moment of Inertia Sum : " << ContactMomentOfInertiaSum << '\n';
	std::cout << '\n';

	std::cout << "MassInverseSum     : " << MassInverseSum << " /kg\n";
	std::cout << "MomentOfInertiaSum : " << MomentOfInertiaSum << " dm/dm\n";
	std::cout << '\n';
	//MomentOfInertiaSum = 0.0f;

	float e = 1.0f;
	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum + MomentOfInertiaSum);

	std::cout << "MassInverseSum     : " << MassInverseSum << " /kg\n";
	std::cout << "MomentOfInertiaSum : " << MomentOfInertiaSum << "\n";
	std::cout << "ImpulseFactor      : " << ImpulseFactor << " kg*dm/s\n";
	std::cout << '\n';

	ResolveData data;
	data.Pos0 = Normal * (ImpulseFactor * MassInverse0);
	data.Pos1 = Normal * (ImpulseFactor * MassInverse1);
	data.Rot0 = Angle2D(Angle::Radians(ContactAxis0 * (ImpulseFactor * MomentOfInertiaInverse0)));
	data.Rot1 = Angle2D(Angle::Radians(ContactAxis1 * (ImpulseFactor * MomentOfInertiaInverse1)));
	return data;
}



void Physics2D::Collide(
	Object & obj0,
	Object & obj1,
	float timeDelta
)
{
	if (obj0.IsStatic && obj1.IsStatic) { return; }

	Physics2D::Collision::ContactData contact_data = Physics2D::Collision::ContactData::CheckContact(obj0, obj1, 1.0f);
	if (!contact_data.Valid) { return; }

	Collision::ContactData::ResolveData resolve_data = contact_data.Resolve(obj0, obj1, timeDelta);
	std::cout << "Resolve.Pos[0] " << resolve_data.Pos0 << " dm/s^2\n";
	std::cout << "Resolve.Pos[1] " << resolve_data.Pos1 << " dm/s^2\n";
	std::cout << "Resolve.Rot[0] " << resolve_data.Rot0 << " dm/dm*s^2\n";
	std::cout << "Resolve.Rot[1] " << resolve_data.Rot1 << " dm/dm*s^2\n";
	std::cout << '\n';

	if (timeDelta != 0.0f)
	{
		if (!obj0.IsStatic) { obj0.ExtData.Vel.Pos -= (resolve_data.Pos0); }
		if (!obj1.IsStatic) { obj1.ExtData.Vel.Pos += (resolve_data.Pos1); }
		if (!obj0.IsStatic) { obj0.ExtData.Vel.Rot -= (resolve_data.Rot0); }
		if (!obj1.IsStatic) { obj1.ExtData.Vel.Rot += (resolve_data.Rot1); }
	}
	if (obj0.IsStatic) { obj0.ExtData.Vel = Trans2D(); }
	if (obj1.IsStatic) { obj1.ExtData.Vel = Trans2D(); }
	(void)timeDelta;
}



Physics2D::ObjectDragData Physics2D::CalculateObjectDragData(Object & obj, Ray2D drag, float scalar)
{
	ObjectDragData data;

	data.Contact = drag.Pos - obj.AbsolutePositionOf(Point2D());

	// subtract the speed of the Contact
	/*{
		Point2D vel = obj.AbsoluteVelocityOf(obj.RelativePositionOf(drag.Pos));
		data.Force = (drag.Dir - vel) * scalar;
	}*/
	// almost good

	// dont just subtract, scale it somehow.
	// scale based on Mass and Velocity and View Zoom ?
	// decrease Force if Velocity goes in the same Direction
	// this is probably easy
	{
		Point2D force = obj.AbsoluteVelocityOf(obj.RelativePositionOf(drag.Pos)) * obj.IntData.Mass;
		//Point2D force = obj.ExtData.Vel.Pos * obj.IntData.Mass;
		data.Force = (drag.Dir - force) * scalar;
	}
	// this works better
	// but hight scalar makes things janky

	float dot = Point2D::dot(data.Force, data.Contact);
	data.ForcePos = (data.Contact * ((dot / data.Contact.length2())));
	data.ForceRot = data.Force - data.ForcePos;

	data.Torque = Point2D::cross(data.Contact, data.ForceRot);

	return data;
}



Physics2D::ObjectForceData Physics2D::ApplyForce(float timeDelta, Object & obj, Ray2D drag, float scalar, bool change)
{
	ObjectForceData data;
	data.Drag = drag;

	Point2D Center = obj.AbsolutePositionOf(Point2D());
	Point2D Origin = drag.Pos;
	data.Contact = Line2D(Center, Origin);

	IntrinsicData & int_data = obj.IntData;
	ExtrinsicData & ext_data = obj.ExtData;
	data.Contact = Line2D(Center, obj.AbsolutePositionOf(int_data.CenterOfMass));

	//std::cout << int_data;
	//std::cout << ext_data;

	ObjectDragData contact_data = CalculateObjectDragData(obj, drag, scalar);
	std::cout << "Contact:\n";
	std::cout << "Contact  : " << contact_data.Contact.length() << " dm\n";
	std::cout << "Force    : " << contact_data.Force.length() << " kg*dm/s^2\n";
	std::cout << "ForcePos : " << contact_data.ForcePos.length() << " kg*dm/s^2\n";
	std::cout << "ForceRot : " << contact_data.ForceRot.length() << " kg*dm/s^2\n";
	std::cout << "Torque   : " << contact_data.Torque << " kg*dm^2/s^2\n";
	std::cout << '\n';

	//data.Force = Ray2D(Origin, contact_data.Force);
	//data.ForcePos = Ray2D(Origin, contact_data.ForcePos);
	//data.ForceRot = Ray2D(Origin, contact_data.ForceRot);

	//Point2D LinearAcceleration = contact_data.Force / int_data.Mass;
	//float AngularAcceleration = contact_data.Torque / int_data.MomentOfInertia;

	//std::cout << "Linear Acceleration  : " << LinearAcceleration.length() << " dm/s^2\n";
	//std::cout << "Angular Acceleration : " << AngularAcceleration << " dm/dm*s^2\n";
	//std::cout << "Linear Acceleration  : " << ext_data.Acl.Pos.length() << " dm/s^2\n";
	//std::cout << "Angular Acceleration : " << ext_data.Acl.Rot.Ang.ToRadians() << " dm/dm*s^2\n";
	//std::cout << '\n';

	//data.ChangePos = Ray2D(Center, LinearAcceleration);
	//data.ChangeRot = Ray2D(Center, Point2D(0, AngularAcceleration));
	//data.ChangePos = Ray2D(Center, ext_data.Acl.Pos);
	//data.ChangeRot = Ray2D(Center, Point2D(0, ext_data.Acl.Rot.Ang.ToRadians()));

	ext_data.Acl.Pos += contact_data.Force / int_data.Mass;
	ext_data.Acl.Rot += Angle2D(Angle::Radians(contact_data.Torque / int_data.MomentOfInertia));

	if (change)
	{
		(void)timeDelta;
		/*if (!obj.IsStatic)
		{
			obj.ExtData.Vel.Pos += LinearAcceleration * timeDelta;
			obj.ExtData.Vel.Rot += Angle::Radians(AngularAcceleration * timeDelta);
		}*/
	}

	return data;
}
