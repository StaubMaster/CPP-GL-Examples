#include "Physics2D/Collision/Resolve.hpp"

#include "DataShow.hpp"



Physics2D::Collision::ResolveData Physics2D::Collision::Resolve(
	Point2D normal,
	Projection & projection,
	Object & obj0,
	Object & obj1,
	float timeDelta
)
{
	(void)timeDelta;

	//Point2D PosRel0 = obj0.RelativePositionOfIndex(contact.Undex0);
	//Point2D PosAbs0 = obj0.AbsolutePositionOf(PosRel0);
	Point2D PosAbs0 = projection.Position;
	Point2D VelAbs0 = obj0.AbsoluteVelocityOf(PosAbs0);

	//Point2D PosRel1 = obj1.RelativePositionOfIndex(contact.Undex1);
	//Point2D PosAbs1 = obj1.AbsolutePositionOf(PosRel1);
	Point2D PosAbs1 = projection.Position;
	Point2D VelAbs1 = obj1.AbsoluteVelocityOf(PosAbs1);

	Point2D Velocity = VelAbs1 - VelAbs0;

	/*{
		Arrow2D::Object arrows(4);
		arrows[0] = Arrow2D::Inst::Data(ColorF4(0.5f, 0.0f, 0.0f), 16.0f, Line2D(obj0.ExtData.Now.Pos, contact.Position));
		arrows[1] = Arrow2D::Inst::Data(ColorF4(0.0f, 0.0f, 0.5f), 16.0f, Line2D(obj1.ExtData.Now.Pos, contact.Position));
		arrows[2] = Arrow2D::Inst::Data(ColorF4(1.0f, 0.5f, 0.5f), 16.0f, Ray2D(contact.Position, obj0.AbsoluteVelocityOf(contact.Position)));
		arrows[3] = Arrow2D::Inst::Data(ColorF4(0.5f, 0.5f, 1.0f), 16.0f, Ray2D(contact.Position, obj1.AbsoluteVelocityOf(contact.Position)));
	}*/

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

	Point2D RelativeContact0 = projection.Position - obj0.ExtData.Now.Pos;
	Point2D RelativeContact1 = projection.Position - obj1.ExtData.Now.Pos;
	//Point2D RelativeContact0 = contact_data.Contact0.PosAbs - obj0.ExtData.Now.Pos;
	//Point2D RelativeContact1 = contact_data.Contact1.PosAbs - obj1.ExtData.Now.Pos;

	//contact_data.Velocity = contact_data.Velocity * timeDelta;
	float NormalVelFactor = Point2D::dot(Velocity, normal);

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

	float ContactAxis0 = Point2D::cross(RelativeContact0, normal);
	float ContactAxis1 = Point2D::cross(RelativeContact1, normal);
	Point2D ContactMomentOfInertia0 = Point2D::cross(ContactAxis0 * MomentOfInertiaInverse0, RelativeContact0);
	Point2D ContactMomentOfInertia1 = Point2D::cross(ContactAxis1 * MomentOfInertiaInverse1, RelativeContact1);
	Point2D ContactMomentOfInertiaSum = ContactMomentOfInertia0 + ContactMomentOfInertia1;

	float MomentOfInertiaSum = Point2D::dot(ContactMomentOfInertiaSum, normal);

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

	//std::cout << "Contact [0] : \n" << contact.Undex0 << '\n';
	//std::cout << "Position Relative : " << contact_data.Contact0.PosRel << '\n';
	//std::cout << "Position Absolute : " << contact_data.Contact0.PosAbs << '\n';
	////std::cout << "Velocity Relative : " << contact_data.Contact0.VelRel << '\n';
	//std::cout << "Velocity Absolute : " << contact_data.Contact0.VelAbs << '\n';
	//std::cout << '\n';

	//std::cout << "Contact [1] : \n" << contact.Undex1 << '\n';
	//std::cout << "Position Relative : " << contact_data.Contact1.PosRel << '\n';
	//std::cout << "Position Absolute : " << contact_data.Contact1.PosAbs << '\n';
	////std::cout << "Velocity Relative : " << contact_data.Contact1.VelRel << '\n';
	//std::cout << "Velocity Absolute : " << contact_data.Contact1.VelAbs << '\n';
	//std::cout << '\n';

	//std::cout << "Contact Position : " << contact_data.Position << " dm\n";
	//std::cout << "Contact Velocity : " << contact_data.Velocity << " dm/s\n";
	std::cout << "Contact Normal   : " << normal << ' ' << normal.length() << '\n';
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
	data.Pos0 = normal * (ImpulseFactor * MassInverse0);
	data.Pos1 = normal * (ImpulseFactor * MassInverse1);
	data.Rot0 = Angle2D(Angle::Radians(ContactAxis0 * (ImpulseFactor * MomentOfInertiaInverse0)));
	data.Rot1 = Angle2D(Angle::Radians(ContactAxis1 * (ImpulseFactor * MomentOfInertiaInverse1)));
	return data;
}



Physics2D::Collision::ResolveData Physics2D::Collision::Resolve(
	ContactData & contact,
	Object & obj0,
	Object & obj1,
	float timeDelta
)
{
	ResolveData data;
	ResolveData temp;
	unsigned int n = contact.Projections.Count();

	for (unsigned int i = 0; i < n; i++)
	{
		temp = Resolve(contact.Normal, contact.Projections[i], obj0, obj1, timeDelta);

		data.Pos0 += temp.Pos0 / n;
		data.Pos1 += temp.Pos1 / n;
		data.Rot0 += temp.Rot0 / n;
		data.Rot1 += temp.Rot1 / n;
	}

	return data;
}
