#include "Physics2D/Collision/ObjectProjection.hpp"
#include <math.h>



Physics2D::Collision::ObjectProjection::~ObjectProjection() { }
Physics2D::Collision::ObjectProjection::ObjectProjection()
	: Box()
	, MinUdx(0xFFFFFFFF)
	, MaxUdx(0xFFFFFFFF)
{ }

Physics2D::Collision::ObjectProjection::ObjectProjection(const ObjectProjection & other)
	: Box(other.Box)
	, MinUdx(other.MinUdx)
	, MaxUdx(other.MaxUdx)
{ }
Physics2D::Collision::ObjectProjection & Physics2D::Collision::ObjectProjection::operator=(const ObjectProjection & other)
{
	Box = other.Box;
	MinUdx = other.MinUdx;
	MaxUdx = other.MaxUdx;
	return *this;
}

void Physics2D::Collision::ObjectProjection::Consider(float val, unsigned int idx)
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

Physics2D::Collision::ObjectProjection Physics2D::Collision::ObjectProjection::Project(
	Point2D normal
	, const Object & obj
)
{
	ObjectProjection data;
	for (unsigned int i = 0; i < obj.CornerCount(); i++)
	{
		Point2D	pos = obj.AbsolutePositionOfIndex((i));
		float dot = Point2D::dot(normal, pos);
		data.Consider(dot, i);
	}
	return data;
}





Physics2D::Collision::ObjectProjectionOverlap::~ObjectProjectionOverlap() { }
Physics2D::Collision::ObjectProjectionOverlap::ObjectProjectionOverlap()
	: Valid(false)
	, Distance(0.0f)
	, Undex0(0xFFFFFFFF)
	, Undex1(0xFFFFFFFF)
{ }

Physics2D::Collision::ObjectProjectionOverlap::ObjectProjectionOverlap(const ObjectProjectionOverlap & other)
	: Valid(other.Valid)
	, Distance(other.Distance)
	, Undex0(other.Undex0)
	, Undex1(other.Undex1)
{ }
Physics2D::Collision::ObjectProjectionOverlap & Physics2D::Collision::ObjectProjectionOverlap::operator=(const ObjectProjectionOverlap & other)
{
	Valid = other.Valid;
	Distance = other.Distance;
	Undex0 = other.Undex0;
	Undex1 = other.Undex1;
	return *this;
}

Physics2D::Collision::ObjectProjectionOverlap Physics2D::Collision::ObjectProjectionOverlap::Overlap(
	Point2D normal
	, const Object & obj0
	, const Object & obj1
)
{
	ObjectProjectionOverlap data;

	Collision::ObjectProjection projection0 = Collision::ObjectProjection::Project(normal, obj0);
	Collision::ObjectProjection projection1 = Collision::ObjectProjection::Project(normal, obj1);

	if (projection0.Box.Intersekt(projection1.Box))
	{
		float diff0 = projection0.Box.Max - projection1.Box.Min;
		float diff1 = projection0.Box.Min - projection1.Box.Max;
		if (fabs(diff0) < fabs(diff1))
		{
			data.Distance = diff0;
			data.Undex0 = projection0.MaxUdx;
			data.Undex1 = projection1.MinUdx;
		}
		else
		{
			data.Distance = diff1;
			data.Undex0 = projection0.MinUdx;
			data.Undex1 = projection1.MaxUdx;
		}
		data.Valid = true;
	}
	return data;
}
