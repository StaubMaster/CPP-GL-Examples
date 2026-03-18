#ifndef  POINT_MASS_2D_HPP
# define POINT_MASS_2D_HPP

# include "ValueType/Point2D.hpp"
# include "Miscellaneous/Container/Member.hpp"

struct Matrix3x3;

struct PointMass2D
{
	Point2D		Point;
	float		Mass;

	~PointMass2D();
	PointMass2D();
	PointMass2D(Point2D point, float mass);

	PointMass2D(const PointMass2D & other);
	PointMass2D & operator=(const PointMass2D & other);

	static float Area(const Container::Member<PointMass2D> point_masses);

	static PointMass2D CenterOfMass(const Container::Member<PointMass2D> point_masses);

	static float MomentOfInertia(const Container::Member<PointMass2D> point_masses);

	static Matrix3x3 InertiaTensor(const Container::Member<PointMass2D> & point_masses);
};

#endif