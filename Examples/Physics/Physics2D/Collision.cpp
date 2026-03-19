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
	, Contact()
	, Distance(INFINITY)
	, Contact0Udx(0xFFFFFFFF)
	, Contact1Udx(0xFFFFFFFF)
{ }

Physics2D::PolyGonContactData::PolyGonContactData(const PolyGonContactData & other)
	: Valid(other.Valid)
	, Normal(other.Normal)
	, Contact(other.Contact)
	, Distance(other.Distance)
	, Contact0Udx(other.Contact0Udx)
	, Contact1Udx(other.Contact1Udx)
{ }
Physics2D::PolyGonContactData & Physics2D::PolyGonContactData::operator=(const PolyGonContactData & other)
{
	Valid = other.Valid;
	Normal = other.Normal;
	Contact = other.Contact;
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
		Point2D pos0 = obj0.AbsolutePositionOf(obj0.CornerFromIndex((obj0.PolyGon() -> Sides[i].Corner0.Udx)));
		Point2D pos1 = obj0.AbsolutePositionOf(obj0.CornerFromIndex((obj0.PolyGon() -> Sides[i].Corner1.Udx)));
		Point2D pos2 = obj0.AbsolutePositionOf(obj0.CornerFromIndex((obj0.PolyGon() -> Sides[i].Corner2.Udx)));

		n = (pos1 - pos0).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Contact = obj1.CornerFromIndex(temp.Contact1Udx);
		if (data.Compare(temp)) { data = temp; }

		n = (pos2 - pos1).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Contact = obj1.CornerFromIndex(temp.Contact1Udx);
		if (data.Compare(temp)) { data = temp; }

		n = (pos0 - pos2).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Contact = obj1.CornerFromIndex(temp.Contact1Udx);
		if (data.Compare(temp)) { data = temp; }
	}

	for (unsigned int i = 0; i < obj1.SideCount(); i++)
	{
		Point2D pos0 = obj1.AbsolutePositionOf(obj1.CornerFromIndex((obj1.PolyGon() -> Sides[i].Corner0.Udx)));
		Point2D pos1 = obj1.AbsolutePositionOf(obj1.CornerFromIndex((obj1.PolyGon() -> Sides[i].Corner1.Udx)));
		Point2D pos2 = obj1.AbsolutePositionOf(obj1.CornerFromIndex((obj1.PolyGon() -> Sides[i].Corner2.Udx)));

		n = (pos1 - pos0).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Contact = obj0.CornerFromIndex(temp.Contact0Udx);
		if (data.Compare(temp)) { data = temp; }

		n = (pos2 - pos1).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Contact = obj0.CornerFromIndex(temp.Contact0Udx);
		if (data.Compare(temp)) { data = temp; }

		n = (pos0 - pos2).perpendicular0().normalize();
		temp = CheckContact(obj0, obj1, n, time);
		if (!temp.Valid) { return ret; }
		temp.Contact = obj0.CornerFromIndex(temp.Contact0Udx);
		if (data.Compare(temp)) { data = temp; }
	}

	ret = data;
	return ret;
}





void Physics2D::CollideLinear(
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

	Point2D RelativeContact0 = Contact0 - obj0.Data.Now.Pos;
	Point2D RelativeContact1 = Contact1 - obj1.Data.Now.Pos;

	float MassInverse0 = 0;
	float MassInverse1 = 0;
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.IntData.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.IntData.Mass; }
	float MassInverseSum = MassInverse0 + MassInverse1;



	float e = 1.0f;
	Point2D vel_rel = obj1.Data.Vel.Pos - obj0.Data.Vel.Pos;
	float NormalVelFactor = Point2D::dot(vel_rel, normal);

	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum);
	std::cout << "ImpulseFactor " << ImpulseFactor << '\n';

	if (!obj0.IsStatic) { obj0.Data.Vel.Pos -= normal * (ImpulseFactor / obj0.IntData.Mass); }
	if (!obj1.IsStatic) { obj1.Data.Vel.Pos += normal * (ImpulseFactor / obj1.IntData.Mass); }

	if (obj0.IsStatic) { obj0.Data.Vel = Trans2D(); }
	if (obj1.IsStatic) { obj1.Data.Vel = Trans2D(); }

	std::cout << '\n';
}

void Physics2D::CollideRotate(
	Object & obj0,
	Object & obj1
)
{
	if (obj0.IsStatic && obj1.IsStatic) { return; }

	// Currently only handles one Contact. Should handle all Contacts
	Physics2D::PolyGonContactData contact_data = Physics2D::PolyGonContactData::CheckContact(obj0, obj1, 1.0f);
	if (!contact_data.Valid) { return; }

	Point2D normal = contact_data.Normal.normalize();

	//Point2D Contact0 = obj0.PolyGon() -> Corners[contact_data.Contact0Udx].Pos;
	//Point2D Contact1 = obj1.PolyGon() -> Corners[contact_data.Contact1Udx].Pos;
	Point2D Contact0 = obj0.AbsolutePositionOf(obj0.CornerFromIndex(contact_data.Contact0Udx));
	Point2D Contact1 = obj1.AbsolutePositionOf(obj1.CornerFromIndex(contact_data.Contact1Udx));

	Point2D RelativeContact0 = Contact0 - obj0.Data.Now.Pos;
	Point2D RelativeContact1 = Contact1 - obj1.Data.Now.Pos;

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
	Point2D vel_rel = obj1.Data.Vel.Pos - obj0.Data.Vel.Pos;
	float NormalVelFactor = Point2D::dot(vel_rel, normal);

	std::cout << "normal           : " << normal << '\n';
	std::cout << "vel_rel          : " << vel_rel << '\n';
	std::cout << "NormalVelFactor  : " << NormalVelFactor << '\n';
	std::cout << "MassInverseSum   : " << MassInverseSum << '\n';
	std::cout << "InertiaFactorSum : " << InertiaFactorSum << '\n';

	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum + InertiaFactorSum);
	std::cout << "ImpulseFactor " << ImpulseFactor << '\n';

	if (!obj0.IsStatic) { obj0.Data.Vel.Pos -= normal * (ImpulseFactor / obj0.IntData.Mass); }
	if (!obj1.IsStatic) { obj1.Data.Vel.Pos += normal * (ImpulseFactor / obj1.IntData.Mass); }

//	My Angle Spinning is "the wrong way". positive should be counter-clockwise, mine is clockwise
	if (!obj0.IsStatic) { obj0.Data.Vel.Rot += Angle::Radians((ContactNormal0_3D * ImpulseFactor).length()); }
	if (!obj1.IsStatic) { obj1.Data.Vel.Rot -= Angle::Radians((ContactNormal1_3D * ImpulseFactor).length()); }

	if (obj0.IsStatic) { obj0.Data.Vel = Trans2D(); }
	if (obj1.IsStatic) { obj1.Data.Vel = Trans2D(); }

	std::cout << '\n';
}

/* Collision:
	get Contact Points
	calculate AbsVel at Contact Point
	use that for all this stuff ?
*/
void Physics2D::Collide(
	Object & obj0,
	Object & obj1
)
{
	if (obj0.IsStatic && obj1.IsStatic) { return; }

	// Currently only handles one Contact. Should handle all Contacts
	// also should calculate exact time of contact ?
	Physics2D::PolyGonContactData contact_data = Physics2D::PolyGonContactData::CheckContact(obj0, obj1, 1.0f);
	if (!contact_data.Valid) { return; }

	//Point2D Contact0 = obj0.AbsolutePositionOf(obj0.CornerFromIndex(contact_data.Contact0Udx));
	//Point2D Contact1 = obj1.AbsolutePositionOf(obj1.CornerFromIndex(contact_data.Contact1Udx));

	//Point2D ContactVel0 = obj0.AbsoluteVelocityOf(obj0.CornerFromIndex(contact_data.Contact0Udx));
	//Point2D ContactVel1 = obj1.AbsoluteVelocityOf(obj0.CornerFromIndex(contact_data.Contact0Udx));
	
	Point2D ContactVel0 = obj0.AbsoluteVelocityOf(contact_data.Contact);
	Point2D ContactVel1 = obj1.AbsoluteVelocityOf(contact_data.Contact);

	Point2D RelativeContact0 = contact_data.Contact - obj0.Data.Now.Pos;
	Point2D RelativeContact1 = contact_data.Contact - obj1.Data.Now.Pos;



	float MassInverse0 = 0;
	float MassInverse1 = 0;
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.IntData.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.IntData.Mass; }
	float MassInverseSum = MassInverse0 + MassInverse1;



	Point3D normal_3D(contact_data.Normal.X, contact_data.Normal.Y, 0);
	Point3D RelativeContact0_3D(RelativeContact0.X, RelativeContact0.Y, 0);
	Point3D RelativeContact1_3D(RelativeContact1.X, RelativeContact1.Y, 0);

	Point3D ContactNormal0_3D = Point3D::cross(RelativeContact0_3D, normal_3D);
	Point3D ContactNormal1_3D = Point3D::cross(RelativeContact1_3D, normal_3D);
	Point3D ContactPerpendicular0_3D = Point3D::cross(ContactNormal0_3D, RelativeContact0_3D);
	Point3D ContactPerpendicular1_3D = Point3D::cross(ContactNormal1_3D, RelativeContact1_3D);
	Point3D ContactPerpendicularSum_3D = ContactPerpendicular0_3D + ContactPerpendicular1_3D;

	float InertiaFactorSum = Point2D::dot(Point2D(ContactPerpendicularSum_3D.X, ContactPerpendicularSum_3D.Y), contact_data.Normal);



	std::cout << '\n';
	std::cout << "normal_3D: " << normal_3D << ' ' << normal_3D.length() << '\n';
	std::cout << "RelativeContact0_3D: " << RelativeContact0_3D << ' ' << RelativeContact0_3D.length() << '\n';
	std::cout << "RelativeContact1_3D: " << RelativeContact1_3D << ' ' << RelativeContact1_3D.length() << '\n';
	std::cout << "ContactPerpendicular0_3D: " << ContactPerpendicular0_3D << ' ' << ContactPerpendicular0_3D.length() << '\n';
	std::cout << "ContactPerpendicular1_3D: " << ContactPerpendicular1_3D << ' ' << ContactPerpendicular1_3D.length() << '\n';
	std::cout << "ContactPerpendicularSum_3D: " << ContactPerpendicularSum_3D << ' ' << ContactPerpendicularSum_3D.length() << '\n';
	std::cout << '\n';



	float e = 1.0f;
	Point2D vel_rel = ContactVel1 - ContactVel0;
	float NormalVelFactor = Point2D::dot(vel_rel, contact_data.Normal);

	std::cout << "Contact          : " << contact_data.Contact << '\n';
	std::cout << "Normal           : " << contact_data.Normal << '\n';

	std::cout << "vel_rel          : " << vel_rel << '\n';
	std::cout << "NormalVelFactor  : " << NormalVelFactor << '\n';
	std::cout << "MassInverseSum   : " << MassInverseSum << '\n';
	std::cout << "InertiaFactorSum : " << InertiaFactorSum << '\n';

	InertiaFactorSum = 0;
	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum + InertiaFactorSum);
	std::cout << "ImpulseFactor " << ImpulseFactor << '\n';

	if (!obj0.IsStatic) { obj0.Data.Vel.Pos -= contact_data.Normal * (ImpulseFactor / obj0.IntData.Mass); }
	if (!obj1.IsStatic) { obj1.Data.Vel.Pos += contact_data.Normal * (ImpulseFactor / obj1.IntData.Mass); }

	if (!obj0.IsStatic) { obj0.Data.Vel.Rot += Angle::Radians((ContactNormal0_3D * ImpulseFactor).length()); }
	if (!obj1.IsStatic) { obj1.Data.Vel.Rot -= Angle::Radians((ContactNormal1_3D * ImpulseFactor).length()); }

	if (obj0.IsStatic) { obj0.Data.Vel = Trans2D(); }
	if (obj1.IsStatic) { obj1.Data.Vel = Trans2D(); }

	std::cout << '\n';
}





/* figure out Moment of Inertia

m : Partical Mass
r : Partical Position
v : linear Velocity
p : linear Momentum
ω : angular Velocity
L : angular Momentum
I : Moment of Intertia

L = I * ω
L = r x p
p = m * v

m is allways the full mass of the Object
since it is Rigid ?

I = L / ω
ω is known
L = r x p
r is known
p = m * v
m is known
v = |r| * ω ?

Orbital Angular Momentum in case of Circel:
I = |r| * |r| * m
ω = |v| / |r|
L = (|r| * |r| * m) % (|v| / |r|)
L = |r| * m * |v|
|v| = |r| * ω

L = |r| * m * |r| * ω
*/

/* Problem
I think the problem is treating the Mass of a Perticle
like the Mass of the Object
*/

/* Moment of Inertia shows how Inertia Tensor is calculated
I = [3, 3]

N : Number of Point Masses
m : Point Mass
r : Vector to Point Mass
i : { 0 1 2 } as { x y z } for r.i
j : { 0 1 2 } as { x y z } for r.j

I[i, j] = sum(k 0 to N) { m[k] * ( |r[k]|^2 * (i == j) - (r.i * r.j)) }

Diagonal Elements:
Ixx = sum(k 0 to N) { m[k] * (y[k]^2 + z[k]^2) }
Iyy = sum(k 0 to N) { m[k] * (z[k]^2 + x[k]^2) }
Izz = sum(k 0 to N) { m[k] * (x[k]^2 + y[k]^2) }

Off Diagonal Elements:
Ixy = Iyx = -sum(k 0 to N) { m[k] * (x[k] * y[k]) }
Izx = Ixz = -sum(k 0 to N) { m[k] * (z[k] * x[k]) }
Iyz = Izy = -sum(k 0 to N) { m[k] * (y[k] * z[k]) }

Ixx is Moment of Inertia around X-Axis when rotated around X-Axis
Ixy is Moment of Inertia around Y-Axis when rotated around Y-Axis
*/

/* Moment of Inertia vs Inertia Tensor
I think the Inertia Tensor is constant per Object
while the Moment of Inertia changes depending on the Axis of Rotation
*/

/* full Mass per Point Mass ?
for a Cuboid (w, h, d)
I = [
	[ (1/12) * m * (h^2 + d^2) 0 0 ]
	[ 0 (1/12) * m * (d^2 + w^2) 0 ]
	[ 0 0 (1/12) * m * (w^2 + h^2) ]
]
the Loop just multiplys stuff
this gives each Point (1/12) of the full Mass
since there are 8 Points, that gives (8/12) ?
where is the rest ? in the Middle ?
how is this calculated

Mass should be uniform
so each Point should have the same
but then with 8 Points each should have (1/8) of the Mass

(1/12) comes as a Sum of all Points
so each Point only has ((1/12)/8)
so only (1/96), that is very small
*/





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

	std::cout << int_data;
	std::cout << ext_data;

	ObjectDragData contact_data = CalculateObjectDragData(obj, drag, scalar);
	std::cout << "Contact:\n";
	std::cout << "Contact  : " << contact_data.Contact.length() << " dm\n";
	std::cout << "Force    : " << contact_data.Force.length() << " kg*dm/s^2\n";
	std::cout << "ForcePos : " << contact_data.ForcePos.length() << " kg*dm/s^2\n";
	std::cout << "ForceRot : " << contact_data.ForceRot.length() << " kg*dm/s^2\n";
	std::cout << "Torque   : " << contact_data.Torque << " kg*dm^2/s^2\n";
	std::cout << '\n';

	data.Force = Ray2D(Origin, contact_data.Force);
	data.ForcePos = Ray2D(Origin, contact_data.ForcePos);
	data.ForceRot = Ray2D(Origin, contact_data.ForceRot);

	Point2D LinearAcceleration = contact_data.Force / int_data.Mass;
	float AngularAcceleration = contact_data.Torque / int_data.MomentOfInertia;

	std::cout << "Linear Acceleration  : " << LinearAcceleration.length() << " dm/s^2\n";
	std::cout << "Angular Acceleration : " << AngularAcceleration << " dm/dm*s^2\n";
	std::cout << '\n';

	data.ChangePos = Ray2D(Center, LinearAcceleration);
	data.ChangeRot = Ray2D(Center, Point2D(0, AngularAcceleration));

	if (change)
	{
		if (!obj.IsStatic)
		{
			obj.Data.Vel.Pos += LinearAcceleration * timeDelta;
			obj.Data.Vel.Rot += Angle::Radians(AngularAcceleration * timeDelta);
		}
	}

	return data;
}
