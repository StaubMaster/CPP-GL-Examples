#include "ValueType/Line/F3.hpp"
#include "ValueType/Ray/F3.hpp"



LineF3::LineF3(const VectorF3 & origin, const VectorF3 & target)
	: Origin(origin)
	, Target(target)
{ }
LineF3::LineF3(const RayF3 & ray)
	: Origin(ray.Pos)
	, Target(ray.Pos + ray.Dir)
{ }



LineF3 LineF3::Reverse() const
{
	return LineF3(Target, Origin);
}

VectorF3 LineF3::Differance() const
{
	return (Target - Origin);
}
float LineF3::Length() const
{
	return Differance().length();
}

VectorF3 LineF3::Middle() const
{
	return (Origin + Target) / 2;
}
