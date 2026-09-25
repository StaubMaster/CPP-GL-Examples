#include "ValueType/Line/F2.hpp"
#include "ValueType/Ray/F2.hpp"



LineF2::LineF2(const VectorF2 & origin, const VectorF2 & target)
	: Origin(origin)
	, Target(target)
{ }
LineF2::LineF2(const RayF2 & ray)
	: Origin(ray.Pos)
	, Target(ray.Pos + ray.Dir)
{ }



LineF2 LineF2::Reverse() const
{
	return LineF2(Target, Origin);
}

VectorF2 LineF2::Differance() const
{
	return (Target - Origin);
}
float LineF2::Length() const
{
	return Differance().length();
}

VectorF2 LineF2::Middle() const
{
	return (Origin + Target) / 2;
}
VectorF2 LineF2::Normal() const
{
	return Differance().cross(1.0f).normalize();
}
