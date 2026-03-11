#include "Physics2D/Collision.hpp"
#include "PolyGon/Data.hpp"

#include "ValueType/Point3D.hpp"
#include "ValueType/Trans2D.hpp"

#include "DataShow.hpp"

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
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.Mass; }
	float MassInverseSum = MassInverse0 + MassInverse1;



	float e = 1.0f;
	Point2D vel_rel = obj1.Data.Vel.Pos - obj0.Data.Vel.Pos;
	float NormalVelFactor = Point2D::dot(vel_rel, normal);

	float ImpulseFactor = (-(1.0f + e) * NormalVelFactor) / (MassInverseSum);
	std::cout << "ImpulseFactor " << ImpulseFactor << '\n';

	if (!obj0.IsStatic) { obj0.Data.Vel.Pos -= normal * (ImpulseFactor / obj0.Mass); }
	if (!obj1.IsStatic) { obj1.Data.Vel.Pos += normal * (ImpulseFactor / obj1.Mass); }

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
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.Mass; }
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

	if (!obj0.IsStatic) { obj0.Data.Vel.Pos -= normal * (ImpulseFactor / obj0.Mass); }
	if (!obj1.IsStatic) { obj1.Data.Vel.Pos += normal * (ImpulseFactor / obj1.Mass); }

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
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.Mass; }
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

	if (!obj0.IsStatic) { obj0.Data.Vel.Pos -= contact_data.Normal * (ImpulseFactor / obj0.Mass); }
	if (!obj1.IsStatic) { obj1.Data.Vel.Pos += contact_data.Normal * (ImpulseFactor / obj1.Mass); }

	if (!obj0.IsStatic) { obj0.Data.Vel.Rot += Angle::Radians((ContactNormal0_3D * ImpulseFactor).length()); }
	if (!obj1.IsStatic) { obj1.Data.Vel.Rot -= Angle::Radians((ContactNormal1_3D * ImpulseFactor).length()); }

	if (obj0.IsStatic) { obj0.Data.Vel = Trans2D(); }
	if (obj1.IsStatic) { obj1.Data.Vel = Trans2D(); }

	std::cout << '\n';
}




/*
⁺⁻¹²³
Mass:	M	kg
Length:	L	m
Time:	T	s

Velocity:				M ⁰ L⁺¹ T⁻¹		Length / Time
Accelleration:			M ⁰ L⁺¹ T⁻²		Velocity / Time
Force:					M⁺¹ L⁺¹ T⁻²		Accelleration * Mass
Momentum:				M⁺¹ L⁺¹ T⁻¹		Velocity * Mass = Force * Time
Impulse:				M⁺¹ L⁺¹ T⁻¹		Force * Time

Angular_Velocity:		M ⁰ L ⁰ T⁻¹		Time
Angular_Accelleration:	M ⁰ L ⁰ T⁻²		Time * Time
Torque:					M⁺¹ L⁺² T⁻²		Force * Length
Angular_Momentum:		M⁺¹ L⁺² T⁻¹		Torque * Time
Moment_of_Inertia:		M⁺¹ L⁺² T ⁰		Torque / Angular_Accelleration = Angular_Momentum * Time

*/

/*
the body is rigid, so any rotational force allways rotates the whole mass ?
so Torque depends on how much of the Force is Perpendicular to the Distance from the Center
*/

Physics2D::ObjectTorqueData Physics2D::ApplyTorque(float timeDelta, Object & obj, Ray2D drag, float scalar, bool change)
{
	ObjectTorqueData data;
	data.Drag = drag;

	Point2D center = obj.AbsolutePositionOf(Point2D());
	data.Contact = Line2D(center, drag.Pos);

	Point2D RelativeContact = drag.Pos - center;
	float RelativeContactDistance2 = RelativeContact.length2();

	float dot = Point2D::dot(drag.Dir, RelativeContact);

	Point2D ForcePos = (RelativeContact * ((dot / RelativeContactDistance2)));
	Point2D ForceRot = drag.Dir - ForcePos;
	data.ForcePos = Ray2D(drag.Pos, ForcePos);
	data.ForceRot = Ray2D(drag.Pos, ForceRot);

/*
τ = r x F
L = r x p

r : relative_Contact
F : Force
τ : Torque
p : linear Momentum
L : angular Momentum

m : Mass
ω : angular Velocity

L = I * ω
I = r * r * m

L = I * ω
*/

	float Torque = Point2D::cross(RelativeContact, ForceRot);
	data.Torque = Ray2D(center, Point2D(0, Torque));

//	Point2D Momentum_linear = obj.AbsoluteVelocityOf(drag.Pos);
//	float Momentum_angular = Point2D::cross(relative_Contact, Momentum_linear);
//	data.MomentumAngular = Ray2D(center, Point2D(0, Momentum_angular));

	float MomentOfInertia = obj.Mass / RelativeContactDistance2;

	float ChangeRot = (Torque * MomentOfInertia) * scalar;
	data.ChangeRot = Ray2D(center, Point2D(0, ChangeRot));

	if (change)
	{
		if (!obj.IsStatic) { obj.Data.Vel.Rot += Angle::Radians(ChangeRot) * timeDelta; }
		if (obj.IsStatic) { obj.Data.Vel = Trans2D(); }
	}

	return data;
}
Physics2D::ObjectForceData Physics2D::ApplyForce(float timeDelta, Object & obj, Ray2D drag, float scalar, bool change)
{
	(void)scalar;

	ObjectForceData data;
	data.Drag = drag;

	Point2D center = obj.AbsolutePositionOf(Point2D());
	data.Contact = Line2D(center, drag.Pos);

	Point2D RelativeContact = drag.Pos - center;
	float RelativeContactDistance2 = RelativeContact.length2();

	Point2D Force = drag.Dir;
	float dot = Point2D::dot(Force, RelativeContact);

	Point2D ForcePos = (RelativeContact * ((dot / RelativeContactDistance2)));
	Point2D ForceRot = Force - ForcePos;
	data.ForcePos = Ray2D(drag.Pos, ForcePos);
	data.ForceRot = Ray2D(drag.Pos, ForceRot);

	float Torque = Point2D::cross(RelativeContact, ForceRot);
	data.Torque = Ray2D(center, Point2D(0, Torque));

	float MomentOfInertia = obj.Mass / RelativeContactDistance2;

	Point2D ChangePos = Force * timeDelta;
	data.ChangePos = Ray2D(center, ChangePos);

	float ChangeRot = (Torque * MomentOfInertia) * timeDelta;
	data.ChangeRot = Ray2D(center, Point2D(0, ChangeRot));

	if (change)
	{
		//if (!obj.IsStatic) { obj.Data.Vel.Pos += ChangePos; }
		if (!obj.IsStatic) { obj.Data.Vel.Rot += Angle::Radians(ChangeRot); }
		if (obj.IsStatic) { obj.Data.Vel = Trans2D(); }
	}

//	std::cout << '\n';
	return data;
}
