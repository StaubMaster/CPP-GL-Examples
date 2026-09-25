#include "ValueType/Trans/3D.hpp"



Trans3D::Trans3D(const VectorF3 & pos)
	: Position(pos)
	, Rotation()
{ }
Trans3D::Trans3D(const EulerAngle3D & rot)
	: Position()
	, Rotation(rot)
{ }
Trans3D::Trans3D(const VectorF3 & pos, const EulerAngle3D & rot)
	: Position(pos)
	, Rotation(rot)
{ }





VectorF3 Trans3D::forward(const VectorF3 & vec) const
{
	return Rotation.forward(vec) + Position;
}
VectorF3 Trans3D::reverse(const VectorF3 & vec) const
{
	return Rotation.reverse(vec - Position);
}

Trans3D Trans3D::forward(const Trans3D & other) const
{
	return Trans3D(
		forward(         other.Position),
		Rotation.forward(other.Rotation)
	);
}
