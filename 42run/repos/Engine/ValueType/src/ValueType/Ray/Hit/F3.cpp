#include "ValueType/Ray/Hit/F3.hpp"
#include "ValueType/Ray/F3.hpp"



bool RayHitF3::Is() const { return (Ray != nullptr); }



VectorF3 RayHitF3::Pos() const
{
	return (Ray -> Pos) + ((Ray -> Dir) * Interval);
}



RayHitF3::RayHitF3(const RayF3 & ray, float interval)
	: Ray(&ray)
	, Interval(interval)
{ }



bool RayHitF3::Consider(const RayHitF3 & other)
{
	if (other.Is() && (!Is() || other.Interval < Interval))
	{
		*this = other;
		return true;
	}
	return false;
}
