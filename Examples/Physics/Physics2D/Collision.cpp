#include "Physics2D/Collision.hpp"
#include "PolyGon/Data.hpp"

#include "ValueType/Point3D.hpp"
#include "ValueType/Trans2D.hpp"

#include "DataShow.hpp"

#include "IntrinsicData.hpp"
#include "ExtrinsicData.hpp"

#include <cmath>





Physics2D::PolyGonProjectionData::~PolyGonProjectionData() { }
Physics2D::PolyGonProjectionData::PolyGonProjectionData()
	: Box()
	, MinUdx(0xFFFFFFFF)
	, MaxUdx(0xFFFFFFFF)
{ }

Physics2D::PolyGonProjectionData::PolyGonProjectionData(const PolyGonProjectionData & other)
	: Box(other.Box)
	, MinUdx(other.MinUdx)
	, MaxUdx(other.MaxUdx)
{ }
Physics2D::PolyGonProjectionData & Physics2D::PolyGonProjectionData::operator=(const PolyGonProjectionData & other)
{
	Box = other.Box;
	MinUdx = other.MinUdx;
	MaxUdx = other.MaxUdx;
	return *this;
}

void Physics2D::PolyGonProjectionData::Consider(float val, unsigned int idx)
{
	if (MinUdx == 0xFFFFFFFF || val < Box.Min)
	{
		MinUdx = idx;
		Box.Min = val;
	}
	if (MaxUdx == 0xFFFFFFFF || val > Box.Max)
	{
		MaxUdx = idx;
		Box.Max = val;
	}
}

Physics2D::PolyGonProjectionData Physics2D::PolyGonProjectionData::Project(
	const Object & obj,
	Point2D normal
)
{
	PolyGonProjectionData data;
	for (unsigned int i = 0; i < obj.CornerCount(); i++)
	{
		Point2D	pos = obj.AbsolutePositionOf(obj.CornerFromIndex((i)));
		float dot = Point2D::dot(normal, pos);
		data.Consider(dot, i);
	}
	return data;
}





Physics2D::PolyGonContactData::~PolyGonContactData() { }
Physics2D::PolyGonContactData::PolyGonContactData()
	: Valid(false)
	, Normal()
	, Position()
	, Velocity()
	, Distance(INFINITY)
	, Contact0Udx(0xFFFFFFFF)
	, Contact1Udx(0xFFFFFFFF)
{ }

Physics2D::PolyGonContactData::PolyGonContactData(const PolyGonContactData & other)
	: Valid(other.Valid)
	, Normal(other.Normal)
	, Position(other.Position)
	, Velocity(other.Velocity)
	, Distance(other.Distance)
	, Contact0Udx(other.Contact0Udx)
	, Contact1Udx(other.Contact1Udx)
{ }
Physics2D::PolyGonContactData & Physics2D::PolyGonContactData::operator=(const PolyGonContactData & other)
{
	Valid = other.Valid;
	Normal = other.Normal;
	Position = other.Position;
	Velocity = other.Velocity;
	Distance = other.Distance;
	Contact0Udx = other.Contact0Udx;
	Contact1Udx = other.Contact1Udx;
	return *this;
}



bool Physics2D::PolyGonContactData::Compare(const PolyGonContactData & other) const
{
	if (!other.Valid) { return false; }
	if (!Valid) { return true; }
	return (fabs(other.Distance) < fabs(Distance));
}



Physics2D::PolyGonContactData Physics2D::PolyGonContactData::CheckContact(
	const Object & obj0,
	const Object & obj1,
	Point2D normal,
	float time
)
{
	(void)time;

	PolyGonContactData data;
	data.Normal = normal;

	PolyGonProjectionData projData0 = PolyGonProjectionData::Project(obj0, normal);
	PolyGonProjectionData projData1 = PolyGonProjectionData::Project(obj1, normal);

	if (projData0.Box.Intersekt(projData1.Box))
	{
		float diff0 = projData0.Box.Max - projData1.Box.Min;
		float diff1 = projData0.Box.Min - projData1.Box.Max;
		if (fabs(diff0) < fabs(diff1))
		{
			data.Distance = diff0;
			data.Contact0Udx = projData0.MaxUdx;
			data.Contact1Udx = projData1.MinUdx;
		}
		else
		{
			data.Distance = diff1;
			data.Contact0Udx = projData0.MinUdx;
			data.Contact1Udx = projData1.MaxUdx;
		}
		data.Valid = true;
	}
	return data;
}

Physics2D::PolyGonContactData Physics2D::PolyGonContactData::CheckContact(
	const Object & obj0,
	const Object & obj1,
	float time
)
{
	(void)time;

	PolyGonContactData	ret;
	PolyGonContactData	data;
	PolyGonContactData	temp;
	Point2D n;

	for (unsigned int i = 0; i < obj0.SideCount(); i++)
	{
		Point2D pos0 = obj0.AbsolutePositionOf(obj0.CornerFromIndex((obj0.PolyGon().Sides[i].Corner0.Udx)));
		Point2D pos1 = obj0.AbsolutePositionOf(obj0.CornerFromIndex((obj0.PolyGon().Sides[i].Corner1.Udx)));
		Point2D pos2 = obj0.AbsolutePositionOf(obj0.CornerFromIndex((obj0.PolyGon().Sides[i].Corner2.Udx)));

		n = (pos1 - pos0).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Position = obj1.CornerFromIndex(temp.Contact1Udx);
		if (data.Compare(temp)) { data = temp; }

		n = (pos2 - pos1).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Position = obj1.CornerFromIndex(temp.Contact1Udx);
		if (data.Compare(temp)) { data = temp; }

		n = (pos0 - pos2).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Position = obj1.CornerFromIndex(temp.Contact1Udx);
		if (data.Compare(temp)) { data = temp; }
	}

	for (unsigned int i = 0; i < obj1.SideCount(); i++)
	{
		Point2D pos0 = obj1.AbsolutePositionOf(obj1.CornerFromIndex((obj1.PolyGon().Sides[i].Corner0.Udx)));
		Point2D pos1 = obj1.AbsolutePositionOf(obj1.CornerFromIndex((obj1.PolyGon().Sides[i].Corner1.Udx)));
		Point2D pos2 = obj1.AbsolutePositionOf(obj1.CornerFromIndex((obj1.PolyGon().Sides[i].Corner2.Udx)));

		n = (pos1 - pos0).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Position = obj0.CornerFromIndex(temp.Contact0Udx);
		if (data.Compare(temp)) { data = temp; }

		n = (pos2 - pos1).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Position = obj0.CornerFromIndex(temp.Contact0Udx);
		if (data.Compare(temp)) { data = temp; }

		n = (pos0 - pos2).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Position = obj0.CornerFromIndex(temp.Contact0Udx);
		if (data.Compare(temp)) { data = temp; }
	}

	ret = data;
	ret.Velocity = obj1.ExtData.Vel.Pos - obj0.ExtData.Vel.Pos;
	return ret;
}





/*void Physics2D::CollideLinear(
	Object & obj0,
	Object & obj1
)
{
	if (obj0.IsStatic && obj1.IsStatic) { return; }

	// Currently only handles one Contact. Should handle all Contacts
	Physics2D::PolyGonContactData contact_data = Physics2D::PolyGonContactData::CheckContact(obj0, obj1, 1.0f);
	if (!contact_data.Valid) { return; }

	Point2D normal = contact_data.Normal.normalize();

	Point2D Contact0 = obj0.AbsolutePositionOf(obj0.CornerFromIndex(contact_data.Contact0Udx));
	Point2D Contact1 = obj1.AbsolutePositionOf(obj1.CornerFromIndex(contact_data.Contact1Udx));

	Point2D RelativeContact0 = Contact0 - obj0.ExtData.Now.Pos;
	Point2D RelativeContact1 = Contact1 - obj1.ExtData.Now.Pos;

	float MassInverse0 = 0;
	float MassInverse1 = 0;
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.IntData.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.IntData.Mass; }
	float MassInverseSum = MassInverse0 + MassInverse1;



	float e = 1.0f;
	Point2D vel_rel = obj1.ExtData.Vel.Pos - obj0.ExtData.Vel.Pos;
	float NormalVelFactor = Point2D::dot(vel_rel, normal);

	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum);
	std::cout << "ImpulseFactor " << ImpulseFactor << '\n';

	if (!obj0.IsStatic) { obj0.ExtData.Vel.Pos -= normal * (ImpulseFactor / obj0.IntData.Mass); }
	if (!obj1.IsStatic) { obj1.ExtData.Vel.Pos += normal * (ImpulseFactor / obj1.IntData.Mass); }

	if (obj0.IsStatic) { obj0.ExtData.Vel = Trans2D(); }
	if (obj1.IsStatic) { obj1.ExtData.Vel = Trans2D(); }

	std::cout << '\n';
}*/

/*void Physics2D::CollideRotate(
	Object & obj0,
	Object & obj1
)
{
	if (obj0.IsStatic && obj1.IsStatic) { return; }

	// Currently only handles one Contact. Should handle all Contacts
	Physics2D::PolyGonContactData contact_data = Physics2D::PolyGonContactData::CheckContact(obj0, obj1, 1.0f);
	if (!contact_data.Valid) { return; }

	Point2D normal = contact_data.Normal.normalize();

	//Point2D Contact0 = obj0.PolyGon().Corners[contact_data.Contact0Udx].Pos;
	//Point2D Contact1 = obj1.PolyGon().Corners[contact_data.Contact1Udx].Pos;
	Point2D Contact0 = obj0.AbsolutePositionOf(obj0.CornerFromIndex(contact_data.Contact0Udx));
	Point2D Contact1 = obj1.AbsolutePositionOf(obj1.CornerFromIndex(contact_data.Contact1Udx));

	Point2D RelativeContact0 = Contact0 - obj0.ExtData.Now.Pos;
	Point2D RelativeContact1 = Contact1 - obj1.ExtData.Now.Pos;

	float ContactDistance0 = RelativeContact0.length();
	float ContactDistance1 = RelativeContact1.length();
	(void)ContactDistance0;
	(void)ContactDistance1;



	float MassInverse0 = 0;
	float MassInverse1 = 0;
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.IntData.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.IntData.Mass; }
	float MassInverseSum = MassInverse0 + MassInverse1;



	Point3D normal_3D(normal.X, normal.Y, 0);
	Point3D RelativeContact0_3D(RelativeContact0.X, RelativeContact0.Y, 0);
	Point3D RelativeContact1_3D(RelativeContact1.X, RelativeContact1.Y, 0);

	Point3D ContactNormal0_3D = Point3D::cross(RelativeContact0_3D, normal_3D);
	Point3D ContactNormal1_3D = Point3D::cross(RelativeContact1_3D, normal_3D);
	Point3D ContactPerpendicular0_3D = Point3D::cross(ContactNormal0_3D, RelativeContact0_3D);
	Point3D ContactPerpendicular1_3D = Point3D::cross(ContactNormal1_3D, RelativeContact1_3D);
	Point3D ContactPerpendicularSum_3D = ContactPerpendicular0_3D + ContactPerpendicular1_3D;

	float InertiaFactorSum = Point2D::dot(Point2D(ContactPerpendicularSum_3D.X, ContactPerpendicularSum_3D.Y), normal);



	std::cout << '\n';
	std::cout << "normal_3D: " << normal_3D << ' ' << normal_3D.length() << '\n';
	std::cout << "RelativeContact0_3D: " << RelativeContact0_3D << ' ' << RelativeContact0_3D.length() << '\n';
	std::cout << "RelativeContact1_3D: " << RelativeContact1_3D << ' ' << RelativeContact1_3D.length() << '\n';
	std::cout << "ContactPerpendicular0_3D: " << ContactPerpendicular0_3D << ' ' << ContactPerpendicular0_3D.length() << '\n';
	std::cout << "ContactPerpendicular1_3D: " << ContactPerpendicular1_3D << ' ' << ContactPerpendicular1_3D.length() << '\n';
	std::cout << "ContactPerpendicularSum_3D: " << ContactPerpendicularSum_3D << ' ' << ContactPerpendicularSum_3D.length() << '\n';
	std::cout << '\n';



	float e = 1.0f;
	Point2D vel_rel = obj1.ExtData.Vel.Pos - obj0.ExtData.Vel.Pos;
	float NormalVelFactor = Point2D::dot(vel_rel, normal);

	std::cout << "normal           : " << normal << '\n';
	std::cout << "vel_rel          : " << vel_rel << '\n';
	std::cout << "NormalVelFactor  : " << NormalVelFactor << '\n';
	std::cout << "MassInverseSum   : " << MassInverseSum << '\n';
	std::cout << "InertiaFactorSum : " << InertiaFactorSum << '\n';

	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum + InertiaFactorSum);
	std::cout << "ImpulseFactor " << ImpulseFactor << '\n';

	if (!obj0.IsStatic) { obj0.ExtData.Vel.Pos -= normal * (ImpulseFactor / obj0.IntData.Mass); }
	if (!obj1.IsStatic) { obj1.ExtData.Vel.Pos += normal * (ImpulseFactor / obj1.IntData.Mass); }

//	My Angle Spinning is "the wrong way". positive should be counter-clockwise, mine is clockwise
	if (!obj0.IsStatic) { obj0.ExtData.Vel.Rot += Angle::Radians((ContactNormal0_3D * ImpulseFactor).length()); }
	if (!obj1.IsStatic) { obj1.ExtData.Vel.Rot -= Angle::Radians((ContactNormal1_3D * ImpulseFactor).length()); }

	if (obj0.IsStatic) { obj0.ExtData.Vel = Trans2D(); }
	if (obj1.IsStatic) { obj1.ExtData.Vel = Trans2D(); }

	std::cout << '\n';
}*/



void Physics2D::Collide(
	Object & obj0,
	Object & obj1,
	float timeDelta
)
{
	if (obj0.IsStatic && obj1.IsStatic) { return; }

	Physics2D::PolyGonContactData contact_data = Physics2D::PolyGonContactData::CheckContact(obj0, obj1, 1.0f);
	if (!contact_data.Valid) { return; }

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

	Point2D RelativeContact0 = contact_data.Position - obj0.ExtData.Now.Pos;
	Point2D RelativeContact1 = contact_data.Position - obj1.ExtData.Now.Pos;

//	contact_data.Velocity = contact_data.Velocity * timeDelta;
	float NormalVelFactor = Point2D::dot(contact_data.Velocity, contact_data.Normal);

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

	float ContactAxis0 = Point2D::cross(RelativeContact0, contact_data.Normal);
	float ContactAxis1 = Point2D::cross(RelativeContact1, contact_data.Normal);
	Point2D ContactMomentOfInertia0 = Point2D::cross(ContactAxis0 * MomentOfInertiaInverse0, RelativeContact0);
	Point2D ContactMomentOfInertia1 = Point2D::cross(ContactAxis1 * MomentOfInertiaInverse1, RelativeContact1);
	Point2D ContactMomentOfInertiaSum = ContactMomentOfInertia0 + ContactMomentOfInertia1;

	float MomentOfInertiaSum = Point2D::dot(ContactMomentOfInertiaSum, contact_data.Normal);

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

	std::cout << "Contact Position : " << contact_data.Position << " dm\n";
	std::cout << "Contact Velocity : " << contact_data.Velocity << " dm/s\n";
	std::cout << "Contact Normal   : " << contact_data.Normal << ' ' << contact_data.Normal.length() << '\n';
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
//	MomentOfInertiaSum = 0.0f;

	float e = 1.0f;
	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum + MomentOfInertiaSum);

	std::cout << "MassInverseSum     : " << MassInverseSum << " /kg\n";
	std::cout << "MomentOfInertiaSum : " << MomentOfInertiaSum << "\n";
	std::cout << "ImpulseFactor      : " << ImpulseFactor << " kg*dm/s\n";
	std::cout << '\n';

	Point2D ChangePos0 = contact_data.Normal * (ImpulseFactor * MassInverse0);
	Point2D ChangePos1 = contact_data.Normal * (ImpulseFactor * MassInverse1);
	Angle2D ChangeRot0 = Angle2D(Angle::Radians(ContactAxis0 * (ImpulseFactor * MomentOfInertiaInverse0)));
	Angle2D ChangeRot1 = Angle2D(Angle::Radians(ContactAxis1 * (ImpulseFactor * MomentOfInertiaInverse1)));

	std::cout << "ChangePos[0] " << ChangePos0 << " dm/s^2\n";
	std::cout << "ChangePos[1] " << ChangePos1 << " dm/s^2\n";
	std::cout << "ChangeRot[0] " << ChangeRot0 << " dm/dm*s^2\n";
	std::cout << "ChangeRot[1] " << ChangeRot1 << " dm/dm*s^2\n";
//	std::cout << "Velocity[0] " << obj0.ExtData.Vel.Pos << " dm/s\n";
//	std::cout << "Velocity[1] " << obj1.ExtData.Vel.Pos << " dm/s\n";
	std::cout << '\n';

	if (obj0.IsStatic && obj1.IsStatic)
	{
	}
	else if (obj0.IsStatic != obj1.IsStatic)
	{
		if (!obj0.IsStatic) { obj0.ExtData.Vel.Pos -= ChangePos0 * 2; }
		if (!obj1.IsStatic) { obj1.ExtData.Vel.Pos += ChangePos1 * 2; }
		if (!obj0.IsStatic) { obj0.ExtData.Vel.Rot -= ChangeRot0 * 2; }
		if (!obj1.IsStatic) { obj1.ExtData.Vel.Rot += ChangeRot1 * 2; }
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
	{
		Point2D vel = obj.AbsoluteVelocityOf(obj.RelativePositionOf(drag.Pos));
		data.Force = (drag.Dir - vel) * scalar;
	}

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
	//std::cout << "Contact:\n";
	//std::cout << "Contact  : " << contact_data.Contact.length() << " dm\n";
	//std::cout << "Force    : " << contact_data.Force.length() << " kg*dm/s^2\n";
	//std::cout << "ForcePos : " << contact_data.ForcePos.length() << " kg*dm/s^2\n";
	//std::cout << "ForceRot : " << contact_data.ForceRot.length() << " kg*dm/s^2\n";
	//std::cout << "Torque   : " << contact_data.Torque << " kg*dm^2/s^2\n";
	//std::cout << '\n';

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
