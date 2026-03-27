#include "Physics2D/Collision/Resolve.hpp"

#include "DataShow.hpp"



struct ResolveObjectData
{
	Point2D	AbsoluteVelocity;
	Point2D	RelativePosition;

	float	LinearInertiaInverse;
	float	AngularInertiaInverse;

	float	MomentOfInertiaAxis;
	Point2D	MomentOfInertiaCross;

	ResolveObjectData(Physics2D::Object & obj, Point2D pos, Point2D normal)
	{
		AbsoluteVelocity = obj.AbsoluteVelocityOf(pos);
		RelativePosition = pos - obj.ExtData.Now.Pos;

		if (obj.IsStatic)
		{
			LinearInertiaInverse = 0.0f;
			AngularInertiaInverse = 0.0f;
		}
		else
		{
			LinearInertiaInverse = 1 / obj.IntData.Mass;
			AngularInertiaInverse = 1 / obj.IntData.MomentOfInertia;
		}

		MomentOfInertiaAxis = Point2D::cross(RelativePosition, normal);
		MomentOfInertiaCross = Point2D::cross(AngularInertiaInverse * MomentOfInertiaAxis, RelativePosition);
	}
};



Physics2D::Collision::ResolveData Physics2D::Collision::Resolve(
	Point2D normal,
	Projection & projection,
	Object & obj0,
	Object & obj1,
	float timeDelta
)
{
	(void)timeDelta;

	Point2D Velocity = obj1.AbsoluteVelocityOf(projection.Position) - obj0.AbsoluteVelocityOf(projection.Position);

	std::cout << "Contact\n";
	std::cout << "Normal   : " << normal << ' ' << normal.length() << '\n';
	std::cout << "Position : " << projection.Position << " dm\n";
	std::cout << "Velocity : " << Velocity << " dm/s\n";
	std::cout << '\n';

	ResolveObjectData obj_data_0(obj0, projection.Position, normal);
	ResolveObjectData obj_data_1(obj1, projection.Position, normal);

	// IsStatic assumes and infinite Mass to Inverse Mass is 0
	float MassInverse0 = 0.0f;
	float MassInverse1 = 0.0f;
	if (!obj0.IsStatic) { MassInverse0 = 1 / obj0.IntData.Mass; }
	if (!obj1.IsStatic) { MassInverse1 = 1 / obj1.IntData.Mass; }

	float MassInverseSum = MassInverse0 + MassInverse1;
	//float MassInverseSum = obj_data_0.LinearInertiaInverse + obj_data_1.LinearInertiaInverse;

	float MomentOfInertiaInverse0 = 0.0f;
	float MomentOfInertiaInverse1 = 0.0f;
	if (!obj0.IsStatic) { MomentOfInertiaInverse0 = 1 / obj0.IntData.MomentOfInertia; }
	if (!obj1.IsStatic) { MomentOfInertiaInverse1 = 1 / obj1.IntData.MomentOfInertia; }

	Point2D RelativeContact0 = projection.Position - obj0.ExtData.Now.Pos;
	Point2D RelativeContact1 = projection.Position - obj1.ExtData.Now.Pos;

	std::cout << "IsStatic[0] " << obj0.IsStatic << '\n';
	std::cout << "IsStatic[1] " << obj1.IsStatic << '\n';
	std::cout << "Inverse Linear Mass [0]  : " << (MassInverse0) << '\n';
	std::cout << "Inverse Linear Mass [1]  : " << (MassInverse1) << '\n';
	std::cout << "Inverse Angular Mass [0] : " << (MomentOfInertiaInverse0) << '\n';
	std::cout << "Inverse Angular Mass [1] : " << (MomentOfInertiaInverse1) << '\n';
	std::cout << "Relative[0] " << RelativeContact0 << '\n';
	std::cout << "Relative[1] " << RelativeContact1 << '\n';
	std::cout << '\n';

	float ContactAxis0 = Point2D::cross(RelativeContact0, normal);
	float ContactAxis1 = Point2D::cross(RelativeContact1, normal);
	Point2D ContactMomentOfInertia0 = Point2D::cross(ContactAxis0 * MomentOfInertiaInverse0, RelativeContact0);
	Point2D ContactMomentOfInertia1 = Point2D::cross(ContactAxis1 * MomentOfInertiaInverse1, RelativeContact1);

	Point2D ContactMomentOfInertiaSum = ContactMomentOfInertia0 + ContactMomentOfInertia1;
	float MomentOfInertiaSum = Point2D::dot(ContactMomentOfInertiaSum, normal);

	std::cout << "Contact Axis [0] : " << ContactAxis0 << '\n';
	std::cout << "Contact Axis [1] : " << ContactAxis1 << '\n';
	std::cout << "Contact Moment of Inertia [0] : " << ContactMomentOfInertia0 << '\n';
	std::cout << "Contact Moment of Inertia [1] : " << ContactMomentOfInertia1 << '\n';

	std::cout << "Contact Moment of Inertia Sum : " << ContactMomentOfInertiaSum << '\n';
	std::cout << '\n';

	float e = 1.0f;
	float ImpulseFactor = (Point2D::dot(-(1.0f + e) * Velocity, normal)) / (MassInverseSum + MomentOfInertiaSum);

	std::cout << "MassInverseSum     : " << MassInverseSum << " /kg\n";
	std::cout << "MomentOfInertiaSum : " << MomentOfInertiaSum << "\n";
	std::cout << "ImpulseFactor      : " << ImpulseFactor << " kg*dm/s\n";
	std::cout << '\n';

	ResolveData data;
	data.Pos0 = (ImpulseFactor * MassInverse0) * normal;
	data.Pos1 = (ImpulseFactor * MassInverse1) * normal;
	data.Rot0 = Angle2D(Angle::Radians((ImpulseFactor * MomentOfInertiaInverse0) * ContactAxis0));
	data.Rot1 = Angle2D(Angle::Radians((ImpulseFactor * MomentOfInertiaInverse1) * ContactAxis1));
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
