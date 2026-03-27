#include "Physics2D/Collision/Resolve.hpp"

#include "DataShow.hpp"



struct ResolveObjectData
{
	Point2D	ContactAbsoluteVelocity;
	Point2D	ContactRelativePosition;

	float	LinearInertiaInverse;
	float	AngularInertiaInverse;

	float	MomentOfInertiaAxis;
	Point2D	MomentOfInertiaCross;

	ResolveObjectData(Physics2D::Object & obj, Point2D pos, Point2D normal)
	{
		ContactAbsoluteVelocity = obj.AbsoluteVelocityOf(pos);
		ContactRelativePosition = pos - obj.ExtData.Now.Pos;

		if (obj.IsStatic)
		{
			LinearInertiaInverse = 0.0f;
			AngularInertiaInverse = 0.0f;
		}
		else
		{
			LinearInertiaInverse = 1.0f / obj.IntData.Mass;
			AngularInertiaInverse = 1.0f / obj.IntData.MomentOfInertia;
		}

		MomentOfInertiaAxis = Point2D::cross(ContactRelativePosition, normal);
		MomentOfInertiaCross = Point2D::cross(AngularInertiaInverse * MomentOfInertiaAxis, ContactRelativePosition);
	}

	void ImpulseChange(float ImpulseScalar, Point2D normal, Point2D & change_pos, Angle2D & change_rot)
	{
		change_pos = (ImpulseScalar * LinearInertiaInverse) * normal;
		change_rot = Angle2D(Angle::Radians((ImpulseScalar * AngularInertiaInverse) * MomentOfInertiaAxis));
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

	ResolveObjectData obj_data_0(obj0, projection.Position, normal);
	ResolveObjectData obj_data_1(obj1, projection.Position, normal);

	std::cout << "Contact\n";
	std::cout << "Normal   : " << normal << '\n';
	std::cout << "Position : " << projection.Position << " dm\n";
	std::cout << '\n';

	std::cout << "Contact [0]\n";
	std::cout << "Contact Relative Position : " << obj_data_0.ContactRelativePosition << " dm\n";
	std::cout << "Contact Absolute Velocity : " << obj_data_0.ContactAbsoluteVelocity << " dm/s\n";
	std::cout << "Linear Mass Inverse       : " << obj_data_0.LinearInertiaInverse << " /kg\n";
	std::cout << "Angular Mass Inverse      : " << obj_data_0.AngularInertiaInverse << " /kg*dm*dm\n";
	std::cout << "Moment of Inertia Axis    : " << obj_data_0.MomentOfInertiaAxis << " dm*dm\n";
	std::cout << "Moment of Inertia Cross   : " << obj_data_0.MomentOfInertiaCross << " dm/kg\n";
	std::cout << '\n';

	std::cout << "Contact [1]\n";
	std::cout << "Contact Relative Position : " << obj_data_1.ContactRelativePosition << " dm\n";
	std::cout << "Contact Absolute Velocity : " << obj_data_1.ContactAbsoluteVelocity << " dm/s\n";
	std::cout << "Linear Mass Inverse       : " << obj_data_1.LinearInertiaInverse << " /kg\n";
	std::cout << "Angular Mass Inverse      : " << obj_data_1.AngularInertiaInverse << " /kg*dm*dm\n";
	std::cout << "Moment of Inertia Axis    : " << obj_data_1.MomentOfInertiaAxis << " dm*dm\n";
	std::cout << "Moment of Inertia Cross   : " << obj_data_1.MomentOfInertiaCross << " dm/kg\n";
	std::cout << '\n';

	Point2D Velocity = obj_data_1.ContactAbsoluteVelocity - obj_data_0.ContactAbsoluteVelocity;
	float MassInverseSum = obj_data_0.LinearInertiaInverse + obj_data_1.LinearInertiaInverse;
	Point2D MomentOfInertiaCrossSum = obj_data_0.MomentOfInertiaCross + obj_data_1.MomentOfInertiaCross;

	// could first calculate the dot produects and then sum
	float MomentOfInertiaSum = Point2D::dot(MomentOfInertiaCrossSum, normal);

	//float e = 1.0f;
	float e = obj0.IntData.Restitution * obj1.IntData.Restitution;
	float ImpulseScalar = (Point2D::dot(-(1.0f + e) * Velocity, normal)) / (MassInverseSum + MomentOfInertiaSum);

	std::cout << "Restitution : " << (e) << "\n";
	std::cout << "Restitution : " << (-(1.0f + e)) << "\n";

	std::cout << "Velocity Differance : " << Velocity << " dm/s\n";
	std::cout << "MassInverseSum      : " << MassInverseSum << " /kg\n";
	std::cout << "MomentOfInertiaSum  : " << MomentOfInertiaSum << " /kg\n";
	std::cout << "ImpulseScalar       : " << ImpulseScalar << " kg*dm/s\n";
	std::cout << '\n';

	ResolveData data;
	obj_data_0.ImpulseChange(ImpulseScalar, normal, data.Pos0, data.Rot0);
	obj_data_1.ImpulseChange(ImpulseScalar, normal, data.Pos1, data.Rot1);

	Arrow2D::Object arrows(2);
	(arrows[0] = ColorF4(1, 1, 1)) = Ray2D(projection.Position, data.Pos0);
	(arrows[1] = ColorF4(1, 1, 1)) = Ray2D(projection.Position, data.Pos1);

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
